#ifndef __BIGMATH_MPZ_H
#define __BIGMATH_MPZ_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "bigmath/defines.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int _mp_alloc;
  int _mp_size;
  mp_limb_t *_mp_d;
} __mpz_struct BIGMATH_ATTRIBUTE_ALIGN(sizeof(mp_limb_t));

typedef __mpz_struct mpz_t[1] BIGMATH_ATTRIBUTE_ALIGN(sizeof(mp_limb_t));
typedef __mpz_struct *mpz_ptr;
typedef const __mpz_struct *mpz_srcptr;

void mpz_init(mpz_ptr x) BIGMATH_NOTHROW;

void mpz_init_set(mpz_ptr rop, mpz_srcptr op) BIGMATH_NOTHROW;

void mpz_init_set_ui(mpz_ptr rop, unsigned long int val) BIGMATH_NOTHROW;

void mpz_set(mpz_ptr rop, mpz_srcptr op) BIGMATH_NOTHROW;

void mpz_set_ui(mpz_ptr rop, unsigned long int val) BIGMATH_NOTHROW;

void mpz_init_multiple(mpz_ptr x, ...) BIGMATH_NOTHROW;

void mpz_set_ui_multiple(mpz_ptr x, ...) BIGMATH_NOTHROW;

void mpz_set_multiple(mpz_ptr x, ...) BIGMATH_NOTHROW;

void mpz_init_set_ui_multiple(mpz_ptr x, ...) BIGMATH_NOTHROW;

void mpz_init_set_multiple(mpz_ptr x, ...) BIGMATH_NOTHROW;

void mpz_clear(mpz_ptr x) BIGMATH_NOTHROW;

void mpz_clear_multiple(mpz_ptr x, ...) BIGMATH_NOTHROW;

unsigned long int mpz_get_ui(mpz_srcptr x) BIGMATH_ATTR_PURE BIGMATH_NOTHROW;

long int mpz_get_si(mpz_srcptr x) BIGMATH_ATTR_PURE BIGMATH_NOTHROW;

void mpz_add(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_sub(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_mul(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_add_ui(mpz_ptr rop, mpz_srcptr op1, unsigned long int val) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

void mpz_sub_ui(mpz_ptr rop, mpz_srcptr op1, unsigned long int val) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

void mpz_mul_ui(mpz_ptr rop, mpz_srcptr op1, unsigned long int val) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

void mpz_tdiv_q(mpz_ptr q, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_tdiv_r(mpz_ptr r, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_tdiv_qr(mpz_ptr q, mpz_ptr r, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3, 4);

void mpz_fdiv_q(mpz_ptr q, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_fdiv_r(mpz_ptr r, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_fdiv_qr(mpz_ptr q, mpz_ptr r, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3, 4);

void mpz_cdiv_q(mpz_ptr q, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_cdiv_r(mpz_ptr r, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_cdiv_qr(mpz_ptr q, mpz_ptr r, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3, 4);

void mpz_mod(mpz_ptr r, mpz_srcptr n, mpz_srcptr d) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_pow_ui(mpz_ptr rop, mpz_srcptr base, unsigned long int exp) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

void mpz_powm(mpz_ptr rop, mpz_srcptr base, mpz_srcptr exp, mpz_srcptr mod) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3, 4);

int mpz_cmp(mpz_srcptr op1, mpz_srcptr op2) BIGMATH_ATTR_CONST BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

int mpz_cmp_ui(mpz_srcptr op1, unsigned long int val) BIGMATH_ATTR_CONST BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1);

int mpz_sgn(mpz_srcptr x) BIGMATH_ATTR_CONST BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1);

int mpz_cmpabs(mpz_srcptr op1, mpz_srcptr op2) BIGMATH_ATTR_CONST BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

int mpz_cmp_si(mpz_srcptr op1, signed long int val) BIGMATH_ATTR_CONST BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1);

void mpz_and(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_or(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_xor(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_com(mpz_ptr rop, mpz_srcptr op) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

void mpz_mul_2exp(mpz_ptr rop, mpz_srcptr op, size_t mp_bitcnt_t) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

void mpz_div_2exp(mpz_ptr rop, mpz_srcptr op, size_t mp_bitcnt_t) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

unsigned long int mpz_size(mpz_srcptr x) BIGMATH_ATTR_PURE BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1);

unsigned long int mpz_sizeinbase(mpz_srcptr x, int base) BIGMATH_ATTR_PURE BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1);

char *mpz_get_str(char *str, int base, mpz_srcptr x) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(3) BIGMATH_ATTRIBUTE_WARN_UNUSED_RESULT;

unsigned long int mpz_popcount(mpz_srcptr x) BIGMATH_ATTR_PURE BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1);

int mpz_scan1(mpz_srcptr x, size_t starting_bit) BIGMATH_ATTR_PURE BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1);

void mpz_gcd(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpz_lcm(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr op2) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

int mpz_invert(mpz_ptr rop, mpz_srcptr op1, mpz_srcptr mod) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3) BIGMATH_ATTRIBUTE_WARN_UNUSED_RESULT;

void mpz_neg(mpz_ptr rop, mpz_srcptr op) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

void mpz_abs(mpz_ptr rop, mpz_srcptr op) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

#define ALLOC(x) ((x)->_mp_alloc)
#define PTR(x) ((x)->_mp_d)
#define SIZ(x) ((x)->_mp_size)

#ifdef __cplusplus
}
#endif

#endif
