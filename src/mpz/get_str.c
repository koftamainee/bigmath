#include "bigmath/defines.h"
#include "bigmath/mpn.h"
#include "bigmath/mpz.h"
#include <string.h>

static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

char* mpz_get_str(char* str, int base, mpz_srcptr x) {
  int x_size = mpz_size(x);
  int sign = mpz_sgn(x);

  if (x_size == 0) {
    if (!str) {
      str = (char*)__bigmath_allocate_func(2);
    }
    str[0] = '0';
    str[1] = '\0';
    return str;
  }

  unsigned long int sz = mpz_sizeinbase(x, base) + 2;

  if (!str) {
    str = (char*)__bigmath_allocate_func(sz);
  }

  mp_ptr tmp = __BIGMATH_ALLOC_LIMBS(x_size);
  for (int i = 0; i < x_size; i++) {
    tmp[i] = PTR(x)[i];
  }

  int tmp_size = x_size;
  char* buf = (char*)__bigmath_allocate_func(sz);
  int buf_len = 0;

  mp_limb_t base_limb = (mp_limb_t)base;

  while (tmp_size > 0) {
    mp_limb_t rem = 0;

    for (int i = tmp_size - 1; i >= 0; i--) {
#if defined(__x86_64__) || defined(_M_X64)
      __uint128_t cur = ((__uint128_t)rem << 64) | tmp[i];
      tmp[i] = (mp_limb_t)(cur / base_limb);
      rem = (mp_limb_t)(cur % base_limb);
#else
      mp_limb_t hi = rem;
      mp_limb_t lo = tmp[i];
      mp_limb_t q = 0;
      for (int bit = 63; bit >= 0; bit--) {
        hi = (hi << 1) | (lo >> 63);
        lo <<= 1;
        if (hi >= base_limb) {
          hi -= base_limb;
          q |= ((mp_limb_t)1 << bit);
        }
      }
      tmp[i] = q;
      rem = hi;
#endif
    }

    buf[buf_len++] = digits[rem];

    while (tmp_size > 0 && tmp[tmp_size - 1] == 0) {
      tmp_size--;
    }
  }

  __BIGMATH_FREE_FUNC_LIMBS(tmp, x_size);

  int offset = 0;
  if (sign < 0) {
    str[offset++] = '-';
  }

  for (int i = buf_len - 1; i >= 0; i--) {
    str[offset++] = buf[i];
  }
  str[offset] = '\0';

  __bigmath_free_func(buf, sz);

  return str;
}