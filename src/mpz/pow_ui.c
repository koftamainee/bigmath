#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_pow_ui(mpz_ptr rop, mpz_srcptr base, unsigned long int exp) {
  if (exp == 0) {
    mpz_set_ui(rop, 1);
    return;
  }

  if (mpz_sgn(base) == 0) {
    SIZ(rop) = 0;
    return;
  }

  mpz_t result, b;
  mpz_init_set_ui(result, 1);
  mpz_init_set(b, base);

  while (exp > 0) {
    if (exp & 1) {
      mpz_mul(result, result, b);
    }
    exp >>= 1;
    if (exp > 0) {
      mpz_mul(b, b, b);
    }
  }

  mpz_set(rop, result);

  mpz_clear(result);
  mpz_clear(b);
}