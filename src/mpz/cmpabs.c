#include "bigmath/mpn.h"
#include "bigmath/mpz.h"

int mpz_cmpabs(mpz_srcptr op1, mpz_srcptr op2) {
  int op1_size = (SIZ(op1) >= 0) ? SIZ(op1) : -SIZ(op1);
  int op2_size = (SIZ(op2) >= 0) ? SIZ(op2) : -SIZ(op2);

  if (op1_size != op2_size) return (op1_size > op2_size) ? 1 : -1;

  int cmp = mpn_cmp(PTR(op1), PTR(op2), op1_size);
  return cmp;
}
