#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_lcm(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) {
  if (mpz_sgn(op1) == 0 || mpz_sgn(op2) == 0) {
    SIZ(rop) = 0;
    return;
  }

  mpz_t g, t;
  mpz_init(g);
  mpz_init(t);

  mpz_gcd(g, op1, op2);
  mpz_tdiv_q(t, op1, g);
  mpz_mul(rop, t, op2);
  mpz_abs(rop, rop);

  mpz_clear(g);
  mpz_clear(t);
}