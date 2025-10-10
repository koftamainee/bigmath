#include "bigmath/mpz.h"

void mpz_inits_sets(mpz_ptr rop, ...) {
  va_list args;
  va_start(args, rop);

  while (rop != NULL) {
    mpz_ptr op = va_arg(args, mpz_ptr);
    mpz_init_set(rop, op);
    rop = va_arg(args, mpz_ptr);
  }

  va_end(args);
}
