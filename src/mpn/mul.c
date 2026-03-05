#include "bigmath/mpn.h"
#include <string.h>

void mpn_mul(mp_ptr rp, const mp_limb_t *xp, mp_size_t xn, const mp_limb_t *yp, mp_size_t yn) {
  memset(rp, 0, (xn + yn) * sizeof(mp_limb_t));

  for (mp_size_t i = 0; i < yn; i++) {
    if (yp[i] == 0) {
      continue;
    }
    rp[xn + i] = mpn_addmul_1(rp + i, xp, xn, yp[i]);
  }
}