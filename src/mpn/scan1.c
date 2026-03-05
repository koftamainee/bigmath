#include "bigmath/mpn.h"

size_t mpn_scan1(const mp_limb_t *xp, mp_size_t n, size_t start_bit) {
  size_t limb_bits = sizeof(mp_limb_t) * 8;
  size_t limb_idx = start_bit / limb_bits;
  size_t bit_idx = start_bit % limb_bits;

  for (mp_size_t i = (mp_size_t)limb_idx; i < n; i++) {
    mp_limb_t x = xp[i] >> bit_idx;

    if (x != 0) {
#if defined(__x86_64__) || defined(_M_X64)
      return (size_t)i * limb_bits + bit_idx + __builtin_ctzll(x);
#else
      size_t pos = 0;
      while ((x & 1) == 0) {
        x >>= 1;
        pos++;
      }
      return (size_t)i * limb_bits + bit_idx + pos;
#endif
    }

    bit_idx = 0;
  }

  return (size_t)n * limb_bits;
}