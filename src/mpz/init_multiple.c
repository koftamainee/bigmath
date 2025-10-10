#include "__mpz.h"

void mpz_init_multiple(int count, ...) {
  va_list args;
  va_start(args, count);

  for (int i = 0; i < count; i++) {
    mpz_ptr x = va_arg(args, mpz_ptr);
    mpz_init(x);
  }

  va_end(args);
}
