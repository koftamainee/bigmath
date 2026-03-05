#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_mul(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) {
  int s1 = mpz_sgn(op1);
  int s2 = mpz_sgn(op2);

  if (s1 == 0 || s2 == 0) {
    SIZ(rop) = 0;
    return;
  }

  int op1_size = mpz_size(op1);
  int op2_size = mpz_size(op2);
  int res_size = op1_size + op2_size;

  mp_ptr tmp = __BIGMATH_ALLOC_LIMBS(res_size);

  mpn_mul(tmp, PTR(op1), op1_size, PTR(op2), op2_size);

  if (ALLOC(rop) < res_size) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(res_size);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), res_size);
    }
    ALLOC(rop) = res_size;
  }

  for (int i = 0; i < res_size; i++) {
    PTR(rop)[i] = tmp[i];
  }

  __BIGMATH_FREE_FUNC_LIMBS(tmp, res_size);

  while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
    res_size--;
  }

  int sign = (s1 == s2) ? 1 : -1;
  SIZ(rop) = sign * res_size;
}