#include "bigmath/defines.h"
#include "bigmath/mpz.h"

unsigned long int mpz_sizeinbase(mpz_srcptr x, int base) {
  int x_size = mpz_size(x);

  if (x_size == 0) {
    return 1;
  }

  size_t limb_bits = sizeof(mp_limb_t) * 8;

  mp_limb_t top = PTR(x)[x_size - 1];
  size_t top_bits = 0;
  while (top > 0) {
    top_bits++;
    top >>= 1;
  }

  size_t total_bits = (size_t)(x_size - 1) * limb_bits + top_bits;

  if (base == 2) {
    return total_bits;
  }

  if (base == 16) {
    return (total_bits + 3) / 4;
  }

  if (base == 8) {
    return (total_bits + 2) / 3;
  }

  double log2_base = 0.0;
  int b = base;
  while (b > 1) {
    log2_base++;
    b >>= 1;
  }

  if (log2_base == 0.0) {
    log2_base = 1.0;
  }

  return (unsigned long int)(total_bits / log2_base) + 2;
}