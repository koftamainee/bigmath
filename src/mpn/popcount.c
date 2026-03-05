#include "bigmath/mpn.h"

size_t mpn_popcount(const mp_limb_t *xp, mp_size_t n) {
  size_t count = 0;

  for (mp_size_t i = 0; i < n; i++) {
    mp_limb_t x = xp[i];

#if defined(__x86_64__) || defined(_M_X64)
    count += __builtin_popcountll(x);
#else
    x = x - ((x >> 1) & 0x5555555555555555UL);
    x = (x & 0x3333333333333333UL) + ((x >> 2) & 0x3333333333333333UL);
    x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0fUL;
    count += (x * 0x0101010101010101UL) >> 56;
#endif
  }

  return count;
}