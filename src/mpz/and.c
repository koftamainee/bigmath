#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_and(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) {
  int op1_size = mpz_size(op1);
  int op2_size = mpz_size(op2);
  int min_size = (op1_size < op2_size) ? op1_size : op2_size;

  if (min_size == 0) {
    SIZ(rop) = 0;
    return;
  }

  if (ALLOC(rop) < min_size) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(min_size);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), min_size);
    }
    ALLOC(rop) = min_size;
  }

  mpn_and_n(PTR(rop), PTR(op1), PTR(op2), min_size);

  int res_size = min_size;
  while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
    res_size--;
  }

  SIZ(rop) = res_size;
}