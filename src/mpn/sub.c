#include "bigmath/mpn.h"

mp_limb_t mpn_sub(mp_ptr rp, const mp_limb_t *xp, mp_size_t xn, const mp_limb_t *yp, mp_size_t yn) {
  mp_limb_t borrow;

  if (xn < yn) {
    borrow = mpn_sub(rp, yp, yn, xp, xn);
    return borrow ? 1 : 0;
  }

  borrow = mpn_sub_n(rp, xp, yp, yn);

  for (mp_size_t i = yn; i < xn; i++) {
    mp_limb_t temp = xp[i] - borrow;
    borrow = (xp[i] < borrow);
    rp[i] = temp;
  }

  return borrow;
}
