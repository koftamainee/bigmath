#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

void mpz_mul_2exp(mpz_ptr rop, mpz_srcptr op, size_t shift) {
  if (mpz_sgn(op) == 0 || shift == 0) {
    mpz_set(rop, op);
    return;
  }

  int op_size = mpz_size(op);
  size_t limb_bits = sizeof(mp_limb_t) * 8;
  size_t limb_shift = shift / limb_bits;
  size_t bit_shift = shift % limb_bits;

  int res_size = op_size + (int)limb_shift + (bit_shift ? 1 : 0);

  if (ALLOC(rop) < res_size) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(res_size);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), res_size);
    }
    ALLOC(rop) = res_size;
  }

  for (size_t i = 0; i < limb_shift; i++) {
    PTR(rop)[i] = 0;
  }

  if (bit_shift) {
    mp_limb_t carry = mpn_lshift(PTR(rop) + limb_shift, PTR(op), op_size, bit_shift);
    PTR(rop)[op_size + limb_shift] = carry;
  } else {
    for (int i = 0; i < op_size; i++) {
      PTR(rop)[i + limb_shift] = PTR(op)[i];
    }
  }

  while (res_size > 0 && PTR(rop)[res_size - 1] == 0) {
    res_size--;
  }

  int sign = mpz_sgn(op) > 0 ? 1 : -1;
  SIZ(rop) = sign * res_size;
}