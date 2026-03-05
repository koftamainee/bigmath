#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_cdiv_r(mpz_ptr r, mpz_srcptr n, mpz_srcptr d) {
  int sn = mpz_sgn(n);
  int sd = mpz_sgn(d);

  mpz_tdiv_r(r, n, d);

  if (sn != 0 && sd != 0 && sn == sd) {
    if (mpz_sgn(r) != 0) {
      mpz_sub(r, r, d);
    }
  }
}