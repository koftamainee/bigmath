#include "bigmath/mpz.h"

int mpz_cmp_ui(mpz_srcptr op1, unsigned long int val) {
  int s1 = mpz_sgn(op1);

  if (s1 < 0) {
    return -1;
  } else if (s1 == 0) {
    return (val == 0) ? 0 : -1;
  }

  if (val == 0) return 1;

  int op1_size = (SIZ(op1) >= 0) ? SIZ(op1) : -SIZ(op1);

  if (op1_size > 1) {
    return 1;
  }

  mp_limb_t op1_limb = PTR(op1)[0];
  if (op1_limb < val)
    return -1;
  else if (op1_limb > val)
    return 1;
  else
    return 0;
}
