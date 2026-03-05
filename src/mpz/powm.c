#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_powm(mpz_ptr rop, mpz_srcptr base, mpz_srcptr exp, mpz_srcptr mod) {
  if (mpz_sgn(mod) == 0) {
    return;
  }

  if (mpz_sgn(exp) == 0) {
    mpz_set_ui(rop, 1);
    return;
  }

  if (mpz_sgn(base) == 0) {
    SIZ(rop) = 0;
    return;
  }

  mpz_t result, b, e;
  mpz_init_set_ui(result, 1);
  mpz_init_set(b, base);
  mpz_init_set(e, exp);

  mpz_mod(b, b, mod);

  int e_size = mpz_size(e);
  size_t total_bits = (size_t)e_size * sizeof(mp_limb_t) * 8;

  for (size_t i = 0; i < total_bits; i++) {
    mp_limb_t limb = PTR(e)[i / (sizeof(mp_limb_t) * 8)];
    int bit = (limb >> (i % (sizeof(mp_limb_t) * 8))) & 1;

    if (bit) {
      mpz_mul(result, result, b);
      mpz_mod(result, result, mod);
    }

    mpz_mul(b, b, b);
    mpz_mod(b, b, mod);
  }

  mpz_set(rop, result);

  mpz_clear(result);
  mpz_clear(b);
  mpz_clear(e);
}