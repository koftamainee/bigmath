#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_mod(mpz_ptr r, mpz_srcptr n, mpz_srcptr d) {
  mpz_fdiv_r(r, n, d);

  if (mpz_sgn(r) < 0) {
    mpz_add(r, r, d);
  }
}