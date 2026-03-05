#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_or(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) {
  int op1_size = mpz_size(op1);
  int op2_size = mpz_size(op2);
  int max_size = (op1_size > op2_size) ? op1_size : op2_size;
  int min_size = (op1_size < op2_size) ? op1_size : op2_size;

  if (max_size == 0) {
    SIZ(rop) = 0;
    return;
  }

  if (ALLOC(rop) < max_size) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(max_size);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), max_size);
    }
    ALLOC(rop) = max_size;
  }

  mpn_ior_n(PTR(rop), PTR(op1), PTR(op2), min_size);

  mpz_srcptr longer = (op1_size > op2_size) ? op1 : op2;
  for (int i = min_size; i < max_size; i++) {
    PTR(rop)[i] = PTR(longer)[i];
  }

  int res_size = max_size;
  while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
    res_size--;
  }

  SIZ(rop) = res_size;
}