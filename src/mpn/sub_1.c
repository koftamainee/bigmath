#include "bigmath/mpn.h"

mp_limb_t mpn_sub_1(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, mp_limb_t val) {
  mp_limb_t borrow = val;

  for (mp_size_t i = 0; i < n; i++) {
    mp_limb_t temp = xp[i] - borrow;
    borrow = (xp[i] < borrow);
    rp[i] = temp;
    if (!borrow) {
      for (mp_size_t j = i + 1; j < n; j++) {
        rp[j] = xp[j];
      }
      return 0;
    }
  }

  return borrow;
}