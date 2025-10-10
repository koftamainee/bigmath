#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_add(mpz_ptr rop, const mpz_srcptr op1, const mpz_srcptr op2) {
  int s1 = mpz_sgn(op1);
  int s2 = mpz_sgn(op2);

  if (s1 != 0 && s2 != 0 && s1 != s2) {
    mpz_sub(rop, op1, op2);
    return;
  }

  if (ALLOC(op1) == 0) {
    mpz_set(rop, op2);
    return;
  }
  if (ALLOC(op2) == 0) {
    mpz_set(rop, op1);
    return;
  }

  int op1_size = mpz_size(op1);
  int op2_size = mpz_size(op2);
  int max_size = (op1_size > op2_size) ? op1_size : op2_size;

  if (ALLOC(rop) < max_size + 1) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(max_size + 1);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), max_size + 1);
    }
    ALLOC(rop) = max_size + 1;
  }

  mp_limb_t carry = mpn_add(PTR(rop), PTR(op1), op1_size, PTR(op2), op2_size);

  int sign = (s1 >= 0) ? 1 : -1;
  SIZ(rop) = sign * (max_size + (carry ? 1 : 0));
  if (carry) {
    PTR(rop)[max_size] = carry;
  }

  while (SIZ(rop) != 0 && PTR(rop)[abs(SIZ(rop)) - 1] == 0) {
    SIZ(rop) += (SIZ(rop) > 0) ? -1 : 1;
  }
}
