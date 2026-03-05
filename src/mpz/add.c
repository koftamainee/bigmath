#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_add(mpz_ptr rop, const mpz_srcptr op1, const mpz_srcptr op2) {
  int s1 = mpz_sgn(op1);
  int s2 = mpz_sgn(op2);

  if (s1 == 0) {
    mpz_set(rop, op2);
    return;
  }
  if (s2 == 0) {
    mpz_set(rop, op1);
    return;
  }

  if (s1 != s2) {
    mpz_srcptr bigger, smaller;
    int sign;

    if (mpz_cmpabs(op1, op2) >= 0) {
      bigger = op1;
      smaller = op2;
      sign = s1;
    } else {
      bigger = op2;
      smaller = op1;
      sign = s2;
    }

    int bigger_size = mpz_size(bigger);
    int smaller_size = mpz_size(smaller);

    if (ALLOC(rop) < bigger_size) {
      if (ALLOC(rop) == 0) {
        PTR(rop) = __BIGMATH_ALLOC_LIMBS(bigger_size);
      } else {
        PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), bigger_size);
      }
      ALLOC(rop) = bigger_size;
    }

    mpn_sub(PTR(rop), PTR(bigger), bigger_size, PTR(smaller), smaller_size);

    int res_size = bigger_size;
    while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
      res_size--;
    }

    SIZ(rop) = (res_size == 0) ? 0 : sign * res_size;
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
  if (carry) {
    PTR(rop)[max_size] = carry;
  }

  int res_size = max_size + (carry ? 1 : 0);
  while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
    res_size--;
  }

  int sign = (s1 > 0) ? 1 : -1;
  SIZ(rop) = sign * res_size;
}