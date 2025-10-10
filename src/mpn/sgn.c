#include "bigmath/mpz.h"

int mpz_sgn(mpz_srcptr x) {
  if (SIZ(x) > 0) return 1;
  if (SIZ(x) < 0) return -1;
  return 0;
}
