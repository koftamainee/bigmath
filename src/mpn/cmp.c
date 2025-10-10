#include "bigmath/defines.h"

int mpn_cmp(const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) {
  for (mp_size_t i = n; i > 0; i--) {
    mp_limb_t a = xp[i - 1];
    mp_limb_t b = yp[i - 1];
    if (a != b) return (a > b) ? 1 : -1;
  }
  return 0;
}
