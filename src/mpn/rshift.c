#include "bigmath/mpn.h"

mp_limb_t mpn_rshift(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, unsigned long int shift) {
  if (n == 0) return 0;

  if (shift == 0) {
    mp_size_t i = n;
    do { i--; rp[i] = xp[i]; } while (i > 0);
    return 0;
  }

  unsigned long int limb_bits = sizeof(mp_limb_t) * 8;
  unsigned long int lshift = limb_bits - shift;

  mp_limb_t carry = 0;
  mp_size_t i = n;
  do {
    i--;
    mp_limb_t temp = xp[i];
    rp[i] = (temp >> shift) | carry;
    carry = temp << lshift;
  } while (i > 0);

  return carry;
}