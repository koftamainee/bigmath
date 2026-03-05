#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

unsigned long int mpz_popcount(mpz_srcptr x) {
  int x_size = mpz_size(x);

  if (x_size == 0) {
    return 0;
  }

  return (unsigned long int)mpn_popcount(PTR(x), x_size);
}