#include "bigmath/mpn.h"

void mpn_com_n(mp_ptr rp, const mp_limb_t *xp, mp_size_t n) {
  for (mp_size_t i = 0; i < n; i++) {
    rp[i] = ~xp[i];
  }
}