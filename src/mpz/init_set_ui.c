#include "bigmath/mpz.h"

void mpz_init_set_ui(mpz_ptr rop, unsigned long int val) {
  mpz_init(rop);
  mpz_set_ui(rop, val);
}
