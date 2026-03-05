#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_cdiv_qr(mpz_ptr q, mpz_ptr r, mpz_srcptr n, mpz_srcptr d) {
  int sn = mpz_sgn(n);
  int sd = mpz_sgn(d);

  mpz_tdiv_qr(q, r, n, d);

  if (sn != 0 && sd != 0 && sn == sd) {
    if (mpz_sgn(r) != 0) {
      mpz_t one;
      mpz_init_set_ui(one, 1);
      mpz_add(q, q, one);
      mpz_clear(one);
      mpz_sub(r, r, d);
    }
  }
}