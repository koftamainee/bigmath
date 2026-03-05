#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_add_ui(mpz_ptr rop, mpz_srcptr op1, unsigned long int val) {
  if (val == 0) {
    mpz_set(rop, op1);
    return;
  }

  if (mpz_sgn(op1) == 0) {
    mpz_set_ui(rop, val);
    return;
  }

  int op1_size = mpz_size(op1);
  int sign = mpz_sgn(op1);

  if (sign > 0) {
    int res_size = op1_size + 1;

    if (ALLOC(rop) < res_size) {
      if (ALLOC(rop) == 0) {
        PTR(rop) = __BIGMATH_ALLOC_LIMBS(res_size);
      } else {
        PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), res_size);
      }
      ALLOC(rop) = res_size;
    }

    mp_limb_t carry = mpn_add_1(PTR(rop), PTR(op1), op1_size, val);
    PTR(rop)[op1_size] = carry;

    while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
      res_size--;
    }

    SIZ(rop) = res_size;
  } else {
    if (op1_size == 1 && PTR(op1)[0] <= val) {
      if (PTR(op1)[0] == val) {
        SIZ(rop) = 0;
      } else {
        if (ALLOC(rop) == 0) {
          PTR(rop) = __BIGMATH_ALLOC_LIMBS(1);
          ALLOC(rop) = 1;
        }
        PTR(rop)[0] = val - PTR(op1)[0];
        SIZ(rop) = 1;
      }
      return;
    }

    if (ALLOC(rop) < op1_size) {
      if (ALLOC(rop) == 0) {
        PTR(rop) = __BIGMATH_ALLOC_LIMBS(op1_size);
      } else {
        PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), op1_size);
      }
      ALLOC(rop) = op1_size;
    }

    mpn_sub_1(PTR(rop), PTR(op1), op1_size, val);

    int res_size = op1_size;
    while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
      res_size--;
    }

    SIZ(rop) = -res_size;
  }
}