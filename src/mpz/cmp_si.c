#include "bigmath/mpz.h"

int mpz_cmp_si(mpz_srcptr op1, signed long int val) {
  int s1 = mpz_sgn(op1);

  if (val < 0) {
    int s2 = -1;
    if (s1 != s2) return s1 - s2;
    unsigned long abs_val = (unsigned long)(-val);
    return mpz_cmp_ui(op1, abs_val);
  } else {
    int s2 = (val == 0) ? 0 : 1;
    if (s1 != s2) return s1 - s2;
    if (val == 0) return 0;
    return mpz_cmp_ui(op1, (unsigned long)val);
  }
}
