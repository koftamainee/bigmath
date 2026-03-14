#include "bigmath/mpz.h"

int mpz_cmp_si(mpz_srcptr op1, signed long int val) {
  int s1 = mpz_sgn(op1);
  if (val < 0) {
    if (s1 >= 0) return 1;
    unsigned long abs_val = -(unsigned long)val;
    int op1_size = -SIZ(op1);
    if (op1_size > 1) return -1;
    mp_limb_t op1_limb = PTR(op1)[0];
    if (op1_limb < abs_val) return 1;
    if (op1_limb > abs_val) return -1;
    return 0;
  } else {
    int s2 = (val == 0) ? 0 : 1;
    if (s1 != s2) return s1 - s2;
    if (val == 0) return 0;
    return mpz_cmp_ui(op1, (unsigned long)val);
  }
}