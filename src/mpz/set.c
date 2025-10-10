#include <string.h>

#include "__defines.h"
#include "__mpz.h"

void mpz_set(mpz_ptr rop, mpz_srcptr op) {
  int n = SIZ(op) < 0 ? -SIZ(op) : SIZ(op);
  if (ALLOC(rop) < n) {
    if (ALLOC(rop) == 0) {
      PTR(rop) = __BIGMATH_ALLOC_LIMBS(n);
    } else {
      PTR(rop) = __BIGMATH_REALLOC_LIMBS(PTR(rop), ALLOC(rop), n);
    }
    ALLOC(rop) = n;
  }

  if (n > 0) {
    memcpy(PTR(rop), PTR(op), sizeof(mp_limb_t) * n);
  }
  SIZ(rop) = SIZ(op);
}
