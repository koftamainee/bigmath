#include "__mpz.h"

void mpz_init_set_ui_multiple(int count, ...) {
  va_list args;
  va_start(args, count);

  for (int i = 0; i < count; i++) {
    mpz_ptr rop = va_arg(args, mpz_ptr);
    unsigned long int val = va_arg(args, unsigned long int);
    mpz_init_set_ui(rop, val);
  }

  va_end(args);
}
