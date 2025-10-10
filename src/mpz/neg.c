#include "bigmath/mpz.h"

void mpz_neg(mpz_ptr rop, mpz_srcptr op) {
  if (rop != op) {
    mpz_set(rop, op);
    return;
  }
  SIZ(rop) = -SIZ(rop);
}
