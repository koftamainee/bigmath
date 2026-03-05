#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

int mpz_scan1(mpz_srcptr x, size_t starting_bit) {
  int x_size = mpz_size(x);

  if (x_size == 0) {
    return -1;
  }

  size_t result = mpn_scan1(PTR(x), x_size, starting_bit);

  if (result >= (size_t)x_size * sizeof(mp_limb_t) * 8) {
    return -1;
  }

  return (int)result;
}