#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "bigmath/mpz.h"

int main() {
  mpz_t a, b, temp;
  mpz_init_set_ui(a, 1);
  mpz_init_set_ui(b, 1);

  for (int i = 0; i < 100000; ++i) {
    mpz_set(temp, b);
    mpz_add(b, a, b);
    mpz_set(a, temp);
  }

  for (int i = 0; i < abs(SIZ(b)); ++i) {
    printf("%lu ", PTR(b)[i]);
  }
  printf("\n");

  mpz_clears(a, b, NULL);
}
