#include "bigmath/mpz.h"

long int mpz_get_si(mpz_srcptr x) {
  if (SIZ(x) == 0) {
    return 0;
  }
  long int val = PTR(x)[0];
  if (SIZ(x) < 0) {
    val = -val;
  }
  return val;
}
