#include "__mpz.h"

void mpz_init_set(mpz_ptr rop, mpz_srcptr op) {
  mpz_init(rop);
  mpz_set(rop, op);
}
