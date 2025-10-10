#include "__defines.h"
#include "__mpz.h"

void mpz_set_ui(mpz_ptr rop, unsigned long int val) {
  if (val == 0) {
    if (ALLOC(rop) > 0) {
      __BIGMATH_FREE_FUNC_LIMBS(PTR(rop), ALLOC(rop));
    }

    ALLOC(rop) = 0;
    PTR(rop) = (mp_ptr)&__bigmath_dummy_limb;
    SIZ(rop) = 0;
    return;
  }

  if (ALLOC(rop) < 1) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(1);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), 1);
    }
    ALLOC(rop) = 1;
  }

  PTR(rop)[0] = (mp_limb_t)val;
  SIZ(rop) = 1;
}
