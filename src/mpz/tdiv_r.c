#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"
#include "tdiv_internal.h"

void mpz_tdiv_r(mpz_ptr r, mpz_srcptr n, mpz_srcptr d) {
  int sn = mpz_sgn(n);

  if (sn == 0) {
    SIZ(r) = 0;
    return;
  }

  mpz_tdiv_qr_unsigned(NULL, r, n, d);

  SIZ(r) = (SIZ(r) == 0) ? 0 : sn * SIZ(r);
}