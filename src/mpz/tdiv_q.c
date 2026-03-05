#include <string.h>

#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_tdiv_q(mpz_ptr q, mpz_srcptr n, mpz_srcptr d) {
  int sn = mpz_sgn(n);
  int sd = mpz_sgn(d);

  if (sn == 0) {
    SIZ(q) = 0;
    return;
  }

  int n_size = mpz_size(n);
  int d_size = mpz_size(d);

  if (n_size < d_size) {
    SIZ(q) = 0;
    return;
  }

  int q_size = n_size - d_size + 1;

  mp_ptr qp = __BIGMATH_ALLOC_LIMBS(q_size);
  mp_ptr rp = __BIGMATH_ALLOC_LIMBS(n_size);

  memset(rp, 0, n_size * sizeof(mp_limb_t));
  for (int i = 0; i < n_size; i++) rp[i] = PTR(n)[i];

  mpn_divrem(qp, q_size, rp, n_size, PTR(d), d_size);

  while (q_size > 0 && qp[q_size - 1] == 0) q_size--;

  if (ALLOC(q) < q_size) {
    if (ALLOC(q) == 0) {
      PTR(q) = __BIGMATH_ALLOC_LIMBS(q_size);
    } else {
      PTR(q) = __BIGMATH_REALLOC_LIMBS(PTR(q), ALLOC(q), q_size);
    }
    ALLOC(q) = q_size;
  }

  for (int i = 0; i < q_size; i++) PTR(q)[i] = qp[i];

  __BIGMATH_FREE_FUNC_LIMBS(qp, n_size - d_size + 1);
  __BIGMATH_FREE_FUNC_LIMBS(rp, n_size);

  int sign = (sn == sd) ? 1 : -1;
  SIZ(q) = (q_size == 0) ? 0 : sign * q_size;
}