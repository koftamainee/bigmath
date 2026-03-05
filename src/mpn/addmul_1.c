#include "bigmath/mpn.h"

mp_limb_t mpn_addmul_1(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, mp_limb_t val) {
  if (val == 0) {
    return 0;
  }

  mp_limb_t carry = 0;

#if defined(__x86_64__) || defined(_M_X64)
  for (mp_size_t i = 0; i < n; i++) {
    __uint128_t prod = (__uint128_t)xp[i] * val + rp[i] + carry;
    rp[i] = (mp_limb_t)prod;
    carry = (mp_limb_t)(prod >> 64);
  }
#else
  for (mp_size_t i = 0; i < n; i++) {
    mp_limb_t hi, lo;
    mp_limb_t x = xp[i];
    mp_limb_t x_lo = x & 0xFFFFFFFF;
    mp_limb_t x_hi = x >> 32;
    mp_limb_t v_lo = val & 0xFFFFFFFF;
    mp_limb_t v_hi = val >> 32;

    mp_limb_t mid1 = x_lo * v_hi;
    mp_limb_t mid2 = x_hi * v_lo;
    lo = x_lo * v_lo;
    hi = x_hi * v_hi;

    mp_limb_t mid = mid1 + mid2;
    hi += (mid < mid1) ? ((mp_limb_t)1 << 32) : 0;

    mp_limb_t lo_with_mid = lo + (mid << 32);
    hi += (lo_with_mid < lo);
    hi += (mid >> 32);

    lo = lo_with_mid + rp[i];
    hi += (lo < lo_with_mid);
    lo = lo + carry;
    hi += (lo < carry);

    carry = hi;
    rp[i] = lo;
  }
#endif

  return carry;
}