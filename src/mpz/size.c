#include <stdlib.h>

#include "bigmath/mpz.h"

unsigned long int mpz_size(mpz_srcptr x) { return abs(SIZ(x)); }
