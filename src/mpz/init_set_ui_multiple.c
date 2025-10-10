#include "bigmath/mpz.h"

void mpz_init_set_ui_multiple(mpz_ptr rop, ...) {
  va_list args;
  va_start(args, rop);

  while (rop != NULL) {
    unsigned long int val = va_arg(args, unsigned long int);
    mpz_init_set_ui(rop, val);
    rop = va_arg(args, mpz_ptr);
  }

  va_end(args);
}
