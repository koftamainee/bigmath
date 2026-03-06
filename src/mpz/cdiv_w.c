#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

unsigned long mpz_cdiv_q_ui(mpz_ptr q, mpz_srcptr n, unsigned long d) {
  unsigned long r = mpz_tdiv_q_ui(q, n, d);

  if (mpz_sgn(n) > 0 && r != 0) {
    mpz_t one;
    mpz_init_set_ui(one, 1);
    mpz_add(q, q, one);
    mpz_clear(one);
    r = d - r;
  }

  return r;
}