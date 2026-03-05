#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_tdiv_qr(mpz_ptr q, mpz_ptr r, mpz_srcptr n, mpz_srcptr d) {
  int sn = mpz_sgn(n);
  int sd = mpz_sgn(d);

  if (sn == 0) {
    SIZ(q) = 0;
    SIZ(r) = 0;
    return;
  }

  int n_size = mpz_size(n);
  int d_size = mpz_size(d);

  if (n_size < d_size) {
    mpz_set(r, n);
    SIZ(q) = 0;
    return;
  }

  int q_size = n_size - d_size + 1;

  mp_ptr qp = __BIGMATH_ALLOC_LIMBS(q_size);
  mp_ptr rp = __BIGMATH_ALLOC_LIMBS(n_size);

  for (int i = 0; i < n_size; i++) rp[i] = PTR(n)[i];

  mpn_divrem(qp, q_size, rp, n_size, PTR(d), d_size);

  int q_actual = q_size;
  while (q_actual > 0 && qp[q_actual - 1] == 0) q_actual--;

  int r_actual = n_size;
  while (r_actual > 0 && rp[r_actual - 1] == 0) r_actual--;

  if (ALLOC(q) < q_actual) {
    if (ALLOC(q) == 0) {
      PTR(q) = __BIGMATH_ALLOC_LIMBS(q_actual);
    } else {
      PTR(q) = __BIGMATH_REALLOC_LIMBS(PTR(q), ALLOC(q), q_actual);
    }
    ALLOC(q) = q_actual;
  }

  if (ALLOC(r) < r_actual) {
    if (ALLOC(r) == 0) {
      PTR(r) = __BIGMATH_ALLOC_LIMBS(r_actual);
    } else {
      PTR(r) = __BIGMATH_REALLOC_LIMBS(PTR(r), ALLOC(r), r_actual);
    }
    ALLOC(r) = r_actual;
  }

  for (int i = 0; i < q_actual; i++) PTR(q)[i] = qp[i];
  for (int i = 0; i < r_actual; i++) PTR(r)[i] = rp[i];

  __BIGMATH_FREE_FUNC_LIMBS(qp, q_size);
  __BIGMATH_FREE_FUNC_LIMBS(rp, n_size);

  int sign = (sn == sd) ? 1 : -1;
  SIZ(q) = (q_actual == 0) ? 0 : sign * q_actual;
  SIZ(r) = (r_actual == 0) ? 0 : sn * r_actual;
}