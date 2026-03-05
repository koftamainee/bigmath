#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_com(mpz_ptr rop, mpz_srcptr op) {
  int op_size = mpz_size(op);

  if (op_size == 0) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(1);
      ALLOC(rop) = 1;
    }
    PTR(rop)[0] = 1;
    SIZ(rop) = -1;
    return;
  }

  if (ALLOC(rop) < op_size) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(op_size);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), op_size);
    }
    ALLOC(rop) = op_size;
  }

  mpn_com_n(PTR(rop), PTR(op), op_size);

  int res_size = op_size;
  while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
    res_size--;
  }

  SIZ(rop) = (mpz_sgn(op) >= 0) ? -res_size : res_size;
}