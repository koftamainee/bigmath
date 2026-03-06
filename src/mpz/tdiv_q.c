#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"
#include "tdiv_internal.h"

void mpz_tdiv_q(mpz_ptr q, mpz_srcptr n, mpz_srcptr d) {
  int sn = mpz_sgn(n);
  int sd = mpz_sgn(d);

  if (sn == 0) {
    SIZ(q) = 0;
    return;
  }

  mpz_tdiv_qr_unsigned(q, NULL, n, d);

  int sign_q = (sn == sd) ? 1 : -1;
  SIZ(q) = (SIZ(q) == 0) ? 0 : sign_q * SIZ(q);
}