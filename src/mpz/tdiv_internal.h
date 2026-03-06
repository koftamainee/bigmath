#pragma once

#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"
#include <string.h>

static inline int mpz_tdiv_qr_unsigned(mpz_ptr q, mpz_ptr r,
                                        mpz_srcptr n, mpz_srcptr d) {
  int n_size = mpz_size(n);
  int d_size = mpz_size(d);

  if (n_size < d_size) {
    if (q) SIZ(q) = 0;
    if (r) mpz_set(r, n);
    return 0;
  }

  int q_size = n_size - d_size + 1;

  mp_ptr qp = __BIGMATH_ALLOC_LIMBS(q_size);
  mp_ptr rp = __BIGMATH_ALLOC_LIMBS(n_size);

  memcpy(rp, PTR(n), n_size * sizeof(mp_limb_t));

  mpn_divrem(qp, q_size, rp, n_size, PTR(d), d_size);

  int q_actual = q_size;
  while (q_actual > 0 && qp[q_actual - 1] == 0) q_actual--;

  int r_actual = n_size;
  while (r_actual > 0 && rp[r_actual - 1] == 0) r_actual--;

  if (q) {
    if (ALLOC(q) < q_actual) {
      PTR(q) = (ALLOC(q) == 0)
        ? __BIGMATH_ALLOC_LIMBS(q_actual)
        : __BIGMATH_REALLOC_LIMBS(PTR(q), ALLOC(q), q_actual);
      ALLOC(q) = q_actual;
    }
    memcpy(PTR(q), qp, q_actual * sizeof(mp_limb_t));
    /* caller sets SIZ(q) with correct sign */
    SIZ(q) = q_actual;
  }

  if (r) {
    if (ALLOC(r) < r_actual) {
      PTR(r) = (ALLOC(r) == 0)
        ? __BIGMATH_ALLOC_LIMBS(r_actual)
        : __BIGMATH_REALLOC_LIMBS(PTR(r), ALLOC(r), r_actual);
      ALLOC(r) = r_actual;
    }
    memcpy(PTR(r), rp, r_actual * sizeof(mp_limb_t));
    SIZ(r) = r_actual;
  }

  __BIGMATH_FREE_FUNC_LIMBS(qp, q_size);
  __BIGMATH_FREE_FUNC_LIMBS(rp, n_size);

  return 1;
}