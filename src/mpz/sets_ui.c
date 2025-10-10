#include "bigmath/mpz.h"

void mpz_sets_ui(mpz_ptr x, ...) {
  va_list args;
  va_start(args, x);

  while (x != NULL) {
    unsigned long int val = va_arg(args, unsigned long int);
    mpz_set_ui(x, val);
    x = va_arg(args, mpz_ptr);
  }

  va_end(args);
}
