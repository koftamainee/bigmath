#include "bigmath/mpn.h"

mp_limb_t mpn_add(mp_ptr rp, const mp_limb_t *xp, mp_size_t xn, const mp_limb_t *yp, mp_size_t yn) {
  mp_limb_t carry;

  if (xn < yn) {
    return mpn_add(rp, yp, yn, xp, xn);
  }

  carry = mpn_add_n(rp, xp, yp, yn);

  for (mp_size_t i = yn; i < xn; i++) {
    mp_limb_t temp = xp[i] + carry;
    carry = (temp < carry);
    rp[i] = temp;
  }

  return carry;
}
