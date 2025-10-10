
#include "bigmath/mpn.h"

mp_limb_t mpn_sub_n(mp_ptr rp, const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) {
  mp_limb_t borrow = 0;

#if defined(__x86_64__) || defined(_M_X64)
  for (mp_size_t i = 0; i < n; i++) {
    __int128_t diff = (__int128_t)xp[i] - yp[i] - borrow;
    rp[i] = (mp_limb_t)diff;
    borrow = (diff < 0) ? 1 : 0;
  }
  return borrow;
#else
  for (mp_size_t i = 0; i < n; i++) {
    mp_limb_t temp = xp[i] - borrow;
    borrow = (xp[i] < borrow);
    temp -= yp[i];
    borrow += (temp > ~yp[i]);
    rp[i] = temp;
  }
  return borrow;
#endif
}
