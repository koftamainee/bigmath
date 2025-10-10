#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "bigmath/mpz.h"

int main() {
  printf("Hello world!\n");
  mpz_t a, b, c, d;
  mpz_init_set_ui(a, 52);
  mpz_init_set_ui(b, 48);
  mpz_init_set_ui(c, 100);
  mpz_init_set_ui(d, 100);

  mpz_add(a, a, b);
  printf("%ld\n", mpz_get_si(a));
  mpz_neg(a, a);
  printf("%ld\n", mpz_get_si(a));
  mpz_sub(a, d, b);
  printf("%ld\n", mpz_get_si(a));
  mpz_clears(a, b, c, d, NULL);
}
