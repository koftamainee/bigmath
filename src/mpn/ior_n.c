#include "bigmath/mpn.h"

void mpn_ior_n(mp_ptr rp, const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) {
  for (mp_size_t i = 0; i < n; i++) {
    rp[i] = xp[i] | yp[i];
  }
}