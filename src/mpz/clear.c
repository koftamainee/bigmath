#include "__defines.h"
#include "__mpz.h"

void mpz_clear(mpz_ptr x) {
  if (ALLOC(x)) {
    __BIGMATH_FREE_FUNC_LIMBS(PTR(x), ALLOC(x));
  }
}
