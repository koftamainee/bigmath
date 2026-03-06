#include "bigmath/mpz.h"

void mpz_gcd(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) {
  if (mpz_sgn(op1) == 0) {
    mpz_abs(rop, op2);
    return;
  }
  if (mpz_sgn(op2) == 0) {
    mpz_abs(rop, op1);
    return;
  }

  mpz_t a, b, t;
  mpz_init_set(a, op1);
  mpz_init_set(b, op2);
  mpz_init(t);

  mpz_abs(a, a);
  mpz_abs(b, b);

  while (mpz_sgn(b) != 0) {

    mpz_mod(t, a, b);
    mpz_set(a, b);
    mpz_set(b, t);
  }

  mpz_set(rop, a);

  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(t);
}