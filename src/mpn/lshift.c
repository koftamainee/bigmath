#include "bigmath/mpn.h"

mp_limb_t mpn_lshift(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, unsigned long int shift) {
  if (shift == 0) {
    for (mp_size_t i = 0; i < n; i++) {
      rp[i] = xp[i];
    }
    return 0;
  }

  unsigned long int limb_bits = sizeof(mp_limb_t) * 8;
  unsigned long int rshift = limb_bits - shift;

  mp_limb_t carry = 0;

  for (mp_size_t i = 0; i < n; i++) {
    mp_limb_t temp = xp[i];
    rp[i] = (temp << shift) | carry;
    carry = temp >> rshift;
  }

  return carry;
}