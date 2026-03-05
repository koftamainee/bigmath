#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

int mpz_invert(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr mod) {
  if (mpz_sgn(mod) == 0 || mpz_sgn(op1) == 0) {
    return 0;
  }

  mpz_t a, m, x0, x1, q, t, orig_m;
  mpz_init_set(a, op1);
  mpz_init_set(m, mod);
  mpz_init_set_ui(x0, 0);
  mpz_init_set_ui(x1, 1);
  mpz_init(q);
  mpz_init(t);
  mpz_init_set(orig_m, mod);

  mpz_abs(a, a);
  mpz_abs(m, m);
  mpz_abs(orig_m, orig_m);

  if (mpz_cmp_ui(m, 1) == 0) {
    SIZ(rop) = 0;
    mpz_clears(a, m, x0, x1, q, t, orig_m, NULL);
    return 0;
  }

  while (mpz_cmp_ui(a, 1) > 0) {
    if (mpz_sgn(m) == 0) {
      SIZ(rop) = 0;
      mpz_clears(a, m, x0, x1, q, t, orig_m, NULL);
      return 0;
    }

    mpz_tdiv_q(q, a, m);

    mpz_set(t, m);
    mpz_mod(m, a, m);
    mpz_set(a, t);

    mpz_set(t, x0);
    mpz_mul(q, q, x0);
    mpz_sub(x0, x1, q);
    mpz_set(x1, t);
  }

  if (mpz_sgn(x1) < 0) {
    mpz_add(x1, x1, orig_m);
  }

  mpz_set(rop, x1);
  mpz_clears(a, m, x0, x1, q, t, orig_m, NULL);

  return 1;
}