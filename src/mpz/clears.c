#include "bigmath/mpz.h"

void mpz_clears(mpz_ptr x, ...) {
  va_list args;
  va_start(args, x);

  while (x != NULL) {
    mpz_clear(x);
    x = va_arg(args, mpz_ptr);
  }

  va_end(args);
}
