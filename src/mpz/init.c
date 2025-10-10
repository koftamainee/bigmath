#include "__mpz.h"

void mpz_init(mpz_ptr x) {
  ALLOC(x) = 0;
  PTR(x) = (mp_ptr)&__bigmath_dummy_limb;
  SIZ(x) = 0;
}
