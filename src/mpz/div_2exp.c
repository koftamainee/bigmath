#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_div_2exp(mpz_ptr rop, mpz_srcptr op, size_t shift) {
  if (mpz_sgn(op) == 0 || shift == 0) {
    mpz_set(rop, op);
    return;
  }

  int op_size = mpz_size(op);
  size_t limb_bits = sizeof(mp_limb_t) * 8;
  size_t limb_shift = shift / limb_bits;
  size_t bit_shift = shift % limb_bits;

  if ((size_t)op_size <= limb_shift) {
    SIZ(rop) = 0;
    return;
  }

  int res_size = op_size - (int)limb_shift;

  if (ALLOC(rop) < res_size) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(res_size);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), res_size);
    }
    ALLOC(rop) = res_size;
  }

  if (bit_shift) {
    mpn_rshift(PTR(rop), PTR(op) + limb_shift, res_size, bit_shift);
  } else {
    for (int i = 0; i < res_size; i++) {
      PTR(rop)[i] = PTR(op)[i + limb_shift];
    }
  }

  while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
    res_size--;
  }

  int sign = mpz_sgn(op) > 0 ? 1 : -1;
  SIZ(rop) = sign * res_size;
}