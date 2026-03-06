#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_com(mpz_ptr rop, mpz_srcptr op) {
  mpz_add_ui(rop, op, 1);
  mpz_neg(rop, rop);
}