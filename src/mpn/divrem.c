#include "bigmath/mpn.h"
#include <string.h>

static mp_size_t mpn_normalize(const mp_limb_t *xp, mp_size_t n) {
  while (n > 0 && xp[n - 1] == 0) n--;
  return n;
}

static int mpn_cmp_n(const mp_limb_t *xp, mp_size_t xn,
                     const mp_limb_t *yp, mp_size_t yn) {
  if (xn != yn) return xn > yn ? 1 : -1;
  return mpn_cmp(xp, yp, xn);
}

static void mpn_sub_inplace(mp_ptr rp, mp_size_t rn,
                            const mp_limb_t *sp, mp_size_t sn) {
  mp_limb_t borrow = 0;
  for (mp_size_t i = 0; i < sn; i++) {
    mp_limb_t temp = rp[i] - sp[i] - borrow;
    borrow = (rp[i] < sp[i] + borrow || (borrow && sp[i] == (mp_limb_t)-1));
    rp[i] = temp;
  }
  for (mp_size_t i = sn; i < rn && borrow; i++) {
    borrow = (rp[i] == 0);
    rp[i]--;
  }
}

mp_limb_t mpn_divrem(mp_ptr qp, mp_size_t qn, mp_ptr rp, mp_size_t rn,
                     const mp_limb_t *dp, mp_size_t dn) {
  mp_size_t rn_actual = mpn_normalize(rp, rn);

  memset(qp, 0, qn * sizeof(mp_limb_t));

  if (mpn_cmp_n(rp, rn_actual, dp, dn) < 0) {
    return 0;
  }

  size_t limb_bits = sizeof(mp_limb_t) * 8;
  mp_size_t dn_actual = mpn_normalize(dp, dn);

  if (rn_actual == 0 || dn_actual == 0) return 0;

  mp_size_t q_limbs = rn_actual - dn_actual;
  mp_size_t q_bits_total = q_limbs * (mp_size_t)limb_bits;

  mp_limb_t top_r = rp[rn_actual - 1];
  mp_limb_t top_d = dp[dn_actual - 1];
  int extra = 0;
  while ((top_r >> extra) > top_d) extra++;
  q_bits_total += extra;

  for (mp_size_t pos = q_bits_total + 1; pos-- > 0;) {
    mp_size_t shift_limbs = pos / limb_bits;
    int shift_bits = (int)(pos % limb_bits);

    mp_size_t shifted_size = dn_actual + shift_limbs + (shift_bits > 0 ? 1 : 0);
    if (shifted_size > rn_actual + 1) continue;

    mp_ptr shifted = (mp_ptr)__bigmath_allocate_func(shifted_size * sizeof(mp_limb_t));
    memset(shifted, 0, shift_limbs * sizeof(mp_limb_t));

    if (shift_bits > 0) {
      mp_limb_t carry = mpn_lshift(shifted + shift_limbs, dp, dn_actual, shift_bits);
      shifted[dn_actual + shift_limbs] = carry;
    } else {
      memcpy(shifted + shift_limbs, dp, dn_actual * sizeof(mp_limb_t));
    }

    mp_size_t shifted_actual = mpn_normalize(shifted, shifted_size);

    if (mpn_cmp_n(rp, rn_actual, shifted, shifted_actual) >= 0) {
      mpn_sub_inplace(rp, rn_actual, shifted, shifted_actual);
      rn_actual = mpn_normalize(rp, rn_actual);

      mp_size_t q_idx = shift_limbs;
      int q_bit = shift_bits;
      if (q_idx < (mp_size_t)qn) {
        qp[q_idx] |= ((mp_limb_t)1 << q_bit);
      }
    }

    __bigmath_free_func(shifted, shifted_size * sizeof(mp_limb_t));

    if (rn_actual < dn_actual) break;
  }

  return 0;
}