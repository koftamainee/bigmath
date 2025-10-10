#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_sub(mpz_ptr rop, const mpz_srcptr op1, const mpz_srcptr op2) {
  int s1 = mpz_sgn(op1);
  int s2 = mpz_sgn(op2);

  if (s1 == 0) {
    mpz_set(rop, op2);
    SIZ(rop) = -SIZ(rop);
    return;
  }
  if (s2 == 0) {
    mpz_set(rop, op1);
    return;
  }

  if (s1 != s2) {  // TODO: mb remove copy and rewrite for multithreading
    mpz_t cp1, cp2;
    mpz_init_set_multiple(cp1, op1, cp2, op2, NULL);
    if (s1 < 0) {
      SIZ(cp1) = -SIZ(cp1);
    } else {
      SIZ(cp2) = -SIZ(cp2);
    }
    mpz_add(rop, cp1, cp2);
    mpz_clear_multiple(cp1, cp2);
    return;
  }

  int op1_size = mpz_size(op1);
  int op2_size = mpz_size(op2);

  mpz_srcptr bigger, smaller;
  int bigger_size, smaller_size;
  int sign;

  if (mpz_cmpabs(op1, op2) >= 0) {
    bigger = op1;
    bigger_size = op1_size;
    smaller = op2;
    smaller_size = op2_size;
    sign = s1;
  } else {
    bigger = op2;
    bigger_size = op2_size;
    smaller = op1;
    smaller_size = op1_size;
    sign = -s1;
  }

  int max_size = bigger_size;

  if (ALLOC(rop) < max_size) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(max_size);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), max_size);
    }
    ALLOC(rop) = max_size;
  }

  (void)mpn_sub(PTR(rop), PTR(bigger), bigger_size, PTR(smaller), smaller_size);

  int res_size = max_size;
  while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
    res_size--;
  }

  SIZ(rop) = (res_size == 0) ? 0 : sign * res_size;
}
