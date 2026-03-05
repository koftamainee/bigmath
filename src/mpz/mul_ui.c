#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_mul_ui(mpz_ptr rop, mpz_srcptr op1, unsigned long int val) {
  if (mpz_sgn(op1) == 0 || val == 0) {
    SIZ(rop) = 0;
    return;
  }

  int op1_size = mpz_size(op1);
  int res_size = op1_size + 1;

  if (ALLOC(rop) < res_size) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(res_size);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), res_size);
    }
    ALLOC(rop) = res_size;
  }

  mp_limb_t carry = mpn_mul_1(PTR(rop), PTR(op1), op1_size, val);
  PTR(rop)[op1_size] = carry;

  while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
    res_size--;
  }

  int sign = (mpz_sgn(op1) > 0) ? 1 : -1;
  SIZ(rop) = sign * res_size;
}