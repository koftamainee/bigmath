#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

int mpz_cmp(mpz_srcptr op1, mpz_srcptr op2) {
  int s1 = mpz_sgn(op1);
  int s2 = mpz_sgn(op2);

  if (s1 != s2) return s1 - s2;

  int op1_size = (SIZ(op1) >= 0) ? SIZ(op1) : -SIZ(op1);
  int op2_size = (SIZ(op2) >= 0) ? SIZ(op2) : -SIZ(op2);

  if (op1_size != op2_size) return (s1 >= 0 ? op1_size - op2_size : op2_size - op1_size);

  int cmp = mpn_cmp(PTR(op1), PTR(op2), op1_size);
  return (s1 >= 0) ? cmp : -cmp;
}
