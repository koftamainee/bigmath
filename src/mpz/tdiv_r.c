#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_tdiv_r(mpz_ptr r, mpz_srcptr n, mpz_srcptr d) {
  int sn = mpz_sgn(n);

  if (sn == 0) {
    SIZ(r) = 0;
    return;
  }

  int n_size = mpz_size(n);
  int d_size = mpz_size(d);

  if (n_size < d_size) {
    mpz_set(r, n);
    return;
  }

  int q_size = n_size - d_size + 1;

  mp_ptr qp = __BIGMATH_ALLOC_LIMBS(q_size);
  mp_ptr rp = __BIGMATH_ALLOC_LIMBS(n_size);

  for (int i = 0; i < n_size; i++) rp[i] = PTR(n)[i];

  mpn_divrem(qp, q_size, rp, n_size, PTR(d), d_size);

  int r_size = n_size;
  while (r_size > 0 && rp[r_size - 1] == 0) r_size--;

  if (ALLOC(r) < r_size) {
    if (ALLOC(r) == 0) {
      PTR(r) = __BIGMATH_ALLOC_LIMBS(r_size);
    } else {
      PTR(r) = __BIGMATH_REALLOC_LIMBS(PTR(r), ALLOC(r), r_size);
    }
    ALLOC(r) = r_size;
  }

  for (int i = 0; i < r_size; i++) PTR(r)[i] = rp[i];

  __BIGMATH_FREE_FUNC_LIMBS(qp, q_size);
  __BIGMATH_FREE_FUNC_LIMBS(rp, n_size);

  SIZ(r) = (r_size == 0) ? 0 : sn * r_size;
}