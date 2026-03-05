#include "bigmath/mpn.h"

mp_limb_t mpn_add_1(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, mp_limb_t val) {
  mp_limb_t carry = val;

  for (mp_size_t i = 0; i < n; i++) {
    mp_limb_t temp = xp[i] + carry;
    carry = (temp < carry);
    rp[i] = temp;
    if (!carry) {
      for (mp_size_t j = i + 1; j < n; j++) {
        rp[j] = xp[j];
      }
      return 0;
    }
  }

  return carry;
}