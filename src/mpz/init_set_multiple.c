#include "__mpz.h"

void mpz_init_set_multiple(int count, ...) {
  va_list args;
  va_start(args, count);

  for (int i = 0; i < count; i++) {
    mpz_ptr rop = va_arg(args, mpz_ptr);
    mpz_ptr op = va_arg(args, mpz_ptr);
    mpz_init_set(rop, op);
  }

  va_end(args);
}
