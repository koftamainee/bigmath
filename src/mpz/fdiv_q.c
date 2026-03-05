#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_fdiv_q(mpz_ptr q, mpz_srcptr n, mpz_srcptr d) {
  int sn = mpz_sgn(n);
  int sd = mpz_sgn(d);

  mpz_tdiv_q(q, n, d);

  if (sn != 0 && sd != 0 && sn != sd) {
    mpz_t r;
    mpz_init(r);
    mpz_tdiv_r(r, n, d);

    if (mpz_sgn(r) != 0) {
      mpz_t one;
      mpz_init_set_ui(one, 1);
      mpz_sub(q, q, one);
      mpz_clear(one);
    }

    mpz_clear(r);
  }
}