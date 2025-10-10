#include "__mpz.h"

unsigned long int mpz_get_ui(mpz_srcptr x) {
  if (SIZ(x) == 0) {
    return 0;
  }
  return PTR(x)[0];
}
