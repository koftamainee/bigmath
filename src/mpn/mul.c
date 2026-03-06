#include "bigmath/mpn.h"
#include "bigmath/defines.h"
#include <string.h>
#include <math.h>

#define KARATSUBA_THRESHOLD 32
#define FFT_THRESHOLD       512
#define PACK_BITS           26

typedef struct { double re, im; } complex_d;

static void mpn_mul_schoolbook(mp_ptr rp,
                               const mp_limb_t *xp, mp_size_t xn,
                               const mp_limb_t *yp, mp_size_t yn);

static void mpn_mul_karatsuba(mp_ptr rp,
                              const mp_limb_t *xp, mp_size_t xn,
                              const mp_limb_t *yp, mp_size_t yn,
                              mp_ptr scratch);

static void mpn_mul_fft(mp_ptr rp,
                        const mp_limb_t *xp, mp_size_t xn,
                        const mp_limb_t *yp, mp_size_t yn);

void mpn_mul(mp_ptr rp,
             const mp_limb_t *xp, mp_size_t xn,
             const mp_limb_t *yp, mp_size_t yn) {
    if (xn < yn) {
        const mp_limb_t *tp; mp_size_t tn;
        tp = xp; xp = yp; yp = tp;
        tn = xn; xn = yn; yn = tn;
    }

    memset(rp, 0, (xn + yn) * sizeof(mp_limb_t));

    if (yn == 0) return;

    if (yn < KARATSUBA_THRESHOLD) {
        mpn_mul_schoolbook(rp, xp, xn, yp, yn);
    } else if (yn < FFT_THRESHOLD) {
        mp_size_t scratch_size = 8 * xn;
        mp_ptr scratch = __BIGMATH_ALLOC_LIMBS(scratch_size);
        memset(scratch, 0, scratch_size * sizeof(mp_limb_t));
        mpn_mul_karatsuba(rp, xp, xn, yp, yn, scratch);
        __BIGMATH_FREE_FUNC_LIMBS(scratch, scratch_size);
    } else {
        mpn_mul_fft(rp, xp, xn, yp, yn);
    }
}

static void mpn_mul_schoolbook(mp_ptr rp,
                               const mp_limb_t *xp, mp_size_t xn,
                               const mp_limb_t *yp, mp_size_t yn) {
    for (mp_size_t i = 0; i < yn; i++) {
        if (yp[i] == 0) continue;
        rp[xn + i] += mpn_addmul_1(rp + i, xp, xn, yp[i]);
    }
}

static void mpn_add_with_carry(mp_ptr rp,
                               const mp_limb_t *xp, mp_size_t xn,
                               const mp_limb_t *yp, mp_size_t yn,
                               mp_size_t out_n) {
    memset(rp, 0, out_n * sizeof(mp_limb_t));
    mp_size_t min_n = xn < yn ? xn : yn;
    mp_limb_t carry = mpn_add_n(rp, xp, yp, min_n);
    const mp_limb_t *tail = (xn > yn) ? xp : yp;
    mp_size_t tail_n = (xn > yn) ? (xn - min_n) : (yn - min_n);
    for (mp_size_t i = 0; i < tail_n; i++) {
        mp_limb_t sum = tail[min_n + i] + carry;
        carry = (sum < tail[min_n + i]) ? 1 : 0;
        rp[min_n + i] = sum;
    }
    rp[min_n + tail_n] = carry;
}

static void mpn_mul_karatsuba(mp_ptr rp,
                              const mp_limb_t *xp, mp_size_t xn,
                              const mp_limb_t *yp, mp_size_t yn,
                              mp_ptr scratch) {
    if (yn < KARATSUBA_THRESHOLD) {
        mpn_mul_schoolbook(rp, xp, xn, yp, yn);
        return;
    }

    mp_size_t k     = yn / 2;
    mp_size_t sum_n = k + 1;

    const mp_limb_t *x0 = xp;      mp_size_t x0n = k;
    const mp_limb_t *x1 = xp + k;  mp_size_t x1n = xn - k;
    const mp_limb_t *y0 = yp;      mp_size_t y0n = k;
    const mp_limb_t *y1 = yp + k;  mp_size_t y1n = yn - k;

    mp_size_t z2_size = x1n + y1n;
    mp_size_t z1_need = 2 * sum_n;
    if (z2_size > z1_need) z1_need = z2_size;
    if (2 * k   > z1_need) z1_need = 2 * k;
    z1_need += 2;

    mp_ptr sum_x  = scratch;
    mp_ptr sum_y  = scratch + sum_n;
    mp_ptr z1_buf = scratch + 2 * sum_n;
    mp_ptr rec_sc = scratch + 2 * sum_n + z1_need;

    memset(rp, 0, (xn + yn) * sizeof(mp_limb_t));
    mpn_mul_karatsuba(rp, x0, x0n, y0, y0n, rec_sc);
    mpn_mul_karatsuba(rp + 2 * k, x1, x1n, y1, y1n, rec_sc);

    mpn_add_with_carry(sum_x, x1, x1n, x0, x0n, sum_n);
    mpn_add_with_carry(sum_y, y1, y1n, y0, y0n, sum_n);

    memset(z1_buf, 0, z1_need * sizeof(mp_limb_t));
    mpn_mul_karatsuba(z1_buf, sum_x, sum_n, sum_y, sum_n, rec_sc);

    mpn_sub_n(z1_buf, z1_buf, rp,         2 * k);
    mpn_sub_n(z1_buf, z1_buf, rp + 2 * k, z2_size);

    mp_size_t add_n = xn + yn - k;
    mpn_add_n(rp + k, rp + k, z1_buf, add_n < z1_need ? add_n : z1_need);
}

static void fft(complex_d *a, mp_size_t n, int invert) {
    for (mp_size_t i = 1, j = 0; i < n; i++) {
        mp_size_t bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) { complex_d t = a[i]; a[i] = a[j]; a[j] = t; }
    }

    for (mp_size_t len = 2; len <= n; len <<= 1) {
        double ang = 2.0 * M_PI / (double)len * (invert ? -1.0 : 1.0);
        complex_d wlen = { cos(ang), sin(ang) };
        for (mp_size_t i = 0; i < n; i += len) {
            complex_d w = { 1.0, 0.0 };
            for (mp_size_t j = 0; j < len / 2; j++) {
                complex_d u = a[i + j];
                complex_d v = {
                    a[i + j + len/2].re * w.re - a[i + j + len/2].im * w.im,
                    a[i + j + len/2].re * w.im + a[i + j + len/2].im * w.re
                };
                a[i + j]         = (complex_d){ u.re + v.re, u.im + v.im };
                a[i + j + len/2] = (complex_d){ u.re - v.re, u.im - v.im };
                w = (complex_d){
                    w.re * wlen.re - w.im * wlen.im,
                    w.re * wlen.im + w.im * wlen.re
                };
            }
        }
    }

    if (invert) {
        double inv_n = 1.0 / (double)n;
        for (mp_size_t i = 0; i < n; i++) {
            a[i].re *= inv_n;
            a[i].im *= inv_n;
        }
    }
}

static void mpn_mul_fft(mp_ptr rp,
                        const mp_limb_t *xp, mp_size_t xn,
                        const mp_limb_t *yp, mp_size_t yn) {
    size_t limb_bits  = sizeof(mp_limb_t) * 8;
    size_t x_coeffs   = ((size_t)xn * limb_bits + PACK_BITS - 1) / PACK_BITS;
    size_t y_coeffs   = ((size_t)yn * limb_bits + PACK_BITS - 1) / PACK_BITS;
    size_t out_coeffs = x_coeffs + y_coeffs;

    size_t fft_n = 1;
    while (fft_n < out_coeffs) fft_n <<= 1;

    complex_d *fa = (complex_d *)__bigmath_allocate_func(fft_n * sizeof(complex_d));
    complex_d *fb = (complex_d *)__bigmath_allocate_func(fft_n * sizeof(complex_d));
    memset(fa, 0, fft_n * sizeof(complex_d));
    memset(fb, 0, fft_n * sizeof(complex_d));

    for (size_t i = 0; i < x_coeffs; i++) {
        size_t bit_lo  = i * PACK_BITS;
        size_t limb_lo = bit_lo / limb_bits;
        int    bit_off = (int)(bit_lo % limb_bits);
        mp_limb_t val  = xp[limb_lo] >> bit_off;
        if ((size_t)bit_off + PACK_BITS > limb_bits && limb_lo + 1 < (size_t)xn)
            val |= xp[limb_lo + 1] << (limb_bits - bit_off);
        fa[i].re = (double)(val & ((1u << PACK_BITS) - 1));
    }

    for (size_t i = 0; i < y_coeffs; i++) {
        size_t bit_lo  = i * PACK_BITS;
        size_t limb_lo = bit_lo / limb_bits;
        int    bit_off = (int)(bit_lo % limb_bits);
        mp_limb_t val  = yp[limb_lo] >> bit_off;
        if ((size_t)bit_off + PACK_BITS > limb_bits && limb_lo + 1 < (size_t)yn)
            val |= yp[limb_lo + 1] << (limb_bits - bit_off);
        fb[i].re = (double)(val & ((1u << PACK_BITS) - 1));
    }

    fft(fa, (mp_size_t)fft_n, 0);
    fft(fb, (mp_size_t)fft_n, 0);

    for (size_t i = 0; i < fft_n; i++) {
        complex_d a = fa[i], b = fb[i];
        fa[i] = (complex_d){
            a.re * b.re - a.im * b.im,
            a.re * b.im + a.im * b.re
        };
    }

    fft(fa, (mp_size_t)fft_n, 1);

    memset(rp, 0, (xn + yn) * sizeof(mp_limb_t));
    unsigned long long carry = 0;
    for (size_t i = 0; i < out_coeffs || carry; i++) {
        unsigned long long coeff = carry + (i < out_coeffs
            ? (unsigned long long)(fa[i].re + 0.5) : 0ULL);
        size_t bit_lo  = i * PACK_BITS;
        size_t limb_lo = bit_lo / limb_bits;
        int    bit_off = (int)(bit_lo % limb_bits);
        if (limb_lo < (size_t)(xn + yn)) {
            rp[limb_lo] |= (mp_limb_t)((coeff & ((1ULL << PACK_BITS) - 1)) << bit_off);
            if ((size_t)bit_off + PACK_BITS > limb_bits && limb_lo + 1 < (size_t)(xn + yn))
                rp[limb_lo + 1] |= (mp_limb_t)(
                    (coeff & ((1ULL << PACK_BITS) - 1)) >> (limb_bits - bit_off));
        }
        carry = coeff >> PACK_BITS;
    }

    __bigmath_free_func(fa, fft_n * sizeof(complex_d));
    __bigmath_free_func(fb, fft_n * sizeof(complex_d));
}