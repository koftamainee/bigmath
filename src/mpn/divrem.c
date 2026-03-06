#include "bigmath/mpn.h"
#include "bigmath/defines.h"
#include <string.h>

mp_limb_t mpn_divrem(mp_ptr qp, mp_size_t qn, mp_ptr rp, mp_size_t rn,
                     const mp_limb_t *dp, mp_size_t dn) {
    while (rn > 0 && rp[rn - 1] == 0) rn--;
    while (dn > 0 && dp[dn - 1] == 0) dn--;

    memset(qp, 0, qn * sizeof(mp_limb_t));

    if (dn == 0 || rn < dn) return 0;

    if (dn == 1) {
        mp_limb_t d   = dp[0];
        mp_limb_t rem = 0;
        mp_size_t i   = rn;
        do {
            i--;
#if defined(__x86_64__) || defined(_M_X64)
            __uint128_t cur = ((__uint128_t)rem << 64) | rp[i];
            if (i < qn) qp[i] = (mp_limb_t)(cur / d);
            rem = (mp_limb_t)(cur % d);
#else
            if (i < qn) qp[i] = rp[i] / d;
            rem = rp[i] % d;
#endif
        } while (i > 0);
        rp[0] = rem;
        for (mp_size_t j = 1; j < rn; j++) rp[j] = 0;
        return 0;
    }

    size_t limb_bits = sizeof(mp_limb_t) * 8;

    int shift = 0;
    {
        mp_limb_t top = dp[dn - 1];
        while ((top & ((mp_limb_t)1 << (limb_bits - 1))) == 0) { top <<= 1; shift++; }
    }

    mp_size_t un = rn + 1;
    mp_ptr up = __BIGMATH_ALLOC_LIMBS(un);
    mp_ptr vp = __BIGMATH_ALLOC_LIMBS(dn);

    if (shift > 0) {
        up[rn] = mpn_lshift(up, rp, rn, shift);
        mpn_lshift(vp, dp, dn, shift);
    } else {
        memcpy(up, rp, rn * sizeof(mp_limb_t));
        up[rn] = 0;
        memcpy(vp, dp, dn * sizeof(mp_limb_t));
    }

    mp_limb_t vn1 = vp[dn - 1];
    mp_limb_t vn2 = vp[dn - 2];

    mp_size_t j = rn - dn;
    do {
        mp_limb_t u0 = up[j + dn];
        mp_limb_t u1 = up[j + dn - 1];
        mp_limb_t u2 = up[j + dn - 2];

        mp_limb_t qhat, rhat;

#if defined(__x86_64__) || defined(_M_X64)
        if (u0 >= vn1) {
            qhat = (mp_limb_t)-1;
            rhat = u1 + vn1;
        } else {
            __uint128_t uu = ((__uint128_t)u0 << 64) | u1;
            qhat = (mp_limb_t)(uu / vn1);
            rhat = (mp_limb_t)(uu % vn1);
        }
        while (rhat < vn1) {
            if ((__uint128_t)qhat * vn2 <= ((__uint128_t)rhat << 64) + u2) break;
            qhat--;
            mp_limb_t new_rhat = rhat + vn1;
            if (new_rhat < rhat) break;
            rhat = new_rhat;
        }
#else
        qhat = u0;
        rhat = u1;
        (void)u2; (void)vn2;
#endif

        mp_limb_t borrow = 0;
        for (mp_size_t i = 0; i < dn; i++) {
#if defined(__x86_64__) || defined(_M_X64)
            __uint128_t prod = (__uint128_t)qhat * vp[i];
            mp_limb_t p_lo   = (mp_limb_t)prod;
            mp_limb_t p_hi   = (mp_limb_t)(prod >> 64);
#else
            mp_limb_t p_lo = qhat * vp[i];
            mp_limb_t p_hi = 0;
#endif
            mp_limb_t prev = up[j + i];
            up[j + i]      = prev - p_lo - borrow;
            borrow = p_hi + (mp_limb_t)(prev < p_lo || prev - p_lo < borrow);
        }
        up[j + dn] -= borrow;

        if (j < qn) qp[j] = qhat;

        if (up[j + dn] != 0) {
            if (j < qn) qp[j]--;
            mp_limb_t carry = 0;
            for (mp_size_t i = 0; i < dn; i++) {
                mp_limb_t prev = up[j + i];
                mp_limb_t sum  = prev + vp[i] + carry;
                carry = (sum < prev || (carry && vp[i] == (mp_limb_t)-1)) ? 1 : 0;
                up[j + i] = sum;
            }
            up[j + dn] += carry;
        }
    } while (j-- > 0);

    if (shift > 0) {
        mpn_rshift(rp, up, dn, shift);
    } else {
        memcpy(rp, up, dn * sizeof(mp_limb_t));
    }
    for (mp_size_t i = dn; i < rn; i++) rp[i] = 0;

    __BIGMATH_FREE_FUNC_LIMBS(up, un);
    __BIGMATH_FREE_FUNC_LIMBS(vp, dn);

    return 0;
}