#include "bigmath/mpz.h"

void mpz_abs(mpz_ptr rop, mpz_srcptr op) {
  if (rop != op) {
    mpz_set(rop, op);
  }
  if (SIZ(rop) < 0) {
    SIZ(rop) = -SIZ(rop);
  }
}
