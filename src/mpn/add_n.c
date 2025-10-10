#include "bigmath/mpn.h"

mp_limb_t mpn_add_n(mp_ptr rp, const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) {
  mp_limb_t carry = 0;

#if defined(__x86_64__) || defined(_M_X64)
  for (mp_size_t i = 0; i < n; i++) {
    __uint128_t sum = (__uint128_t)xp[i] + yp[i] + carry;
    rp[i] = (mp_limb_t)sum;
    carry = (mp_limb_t)(sum >> 64);
  }
  return carry;

#else
  for (mp_size_t i = 0; i < n; i++) {
    mp_limb_t temp = xp[i] + carry;
    carry = (temp < carry);
    temp += yp[i];
    carry += (temp < yp[i]);
    rp[i] = temp;
  }
  return carry;
#endif
}
