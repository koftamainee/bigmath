#include <gtest/gtest.h>
#include <string.h>

extern "C" {
#include "bigmath/mpz.h"
}

TEST(MpzInit, Basic) {
  mpz_t x;
  mpz_init(x);
  EXPECT_EQ(mpz_sgn(x), 0);
  mpz_clear(x);
}

TEST(MpzSetUi, Basic) {
  mpz_t x;
  mpz_init(x);
  mpz_set_ui(x, 42);
  EXPECT_EQ(mpz_get_ui(x), 42UL);
  mpz_clear(x);
}

TEST(MpzGetSi, Negative) {
  mpz_t x;
  mpz_init(x);
  mpz_set_ui(x, 42);
  mpz_neg(x, x);
  EXPECT_EQ(mpz_get_si(x), -42L);
  mpz_clear(x);
}

TEST(MpzAdd, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 100);
  mpz_init_set_ui(b, 200);
  mpz_init(r);
  mpz_add(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 300UL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzAdd, NegativePositive) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 100);
  mpz_init_set_ui(b, 200);
  mpz_neg(a, a);
  mpz_init(r);
  mpz_add(r, a, b);
  EXPECT_EQ(mpz_get_si(r), 100L);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzSub, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 300);
  mpz_init_set_ui(b, 100);
  mpz_init(r);
  mpz_sub(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 200UL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzSub, NegativeResult) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 100);
  mpz_init_set_ui(b, 300);
  mpz_init(r);
  mpz_sub(r, a, b);
  EXPECT_EQ(mpz_get_si(r), -200L);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzMul, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 100);
  mpz_init_set_ui(b, 200);
  mpz_init(r);
  mpz_mul(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 20000UL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzMul, NegativeResult) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 100);
  mpz_init_set_ui(b, 200);
  mpz_neg(a, a);
  mpz_init(r);
  mpz_mul(r, a, b);
  EXPECT_EQ(mpz_get_si(r), -20000L);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzTdivQ, Basic) {
  mpz_t a, b, q;
  mpz_init_set_ui(a, 100);
  mpz_init_set_ui(b, 7);
  mpz_init(q);
  mpz_tdiv_q(q, a, b);
  EXPECT_EQ(mpz_get_ui(q), 14UL);
  mpz_clears(a, b, q, NULL);
}

TEST(MpzTdivR, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 100);
  mpz_init_set_ui(b, 7);
  mpz_init(r);
  mpz_tdiv_r(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 2UL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzMod, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 100);
  mpz_init_set_ui(b, 7);
  mpz_init(r);
  mpz_mod(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 2UL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzPowUi, Basic) {
  mpz_t base, r;
  mpz_init_set_ui(base, 2);
  mpz_init(r);
  mpz_pow_ui(r, base, 10);
  EXPECT_EQ(mpz_get_ui(r), 1024UL);
  mpz_clears(base, r, NULL);
}

TEST(MpzPowUi, ZeroExp) {
  mpz_t base, r;
  mpz_init_set_ui(base, 999);
  mpz_init(r);
  mpz_pow_ui(r, base, 0);
  EXPECT_EQ(mpz_get_ui(r), 1UL);
  mpz_clears(base, r, NULL);
}

TEST(MpzCmp, Equal) {
  mpz_t a, b;
  mpz_init_set_ui(a, 42);
  mpz_init_set_ui(b, 42);
  EXPECT_EQ(mpz_cmp(a, b), 0);
  mpz_clears(a, b, NULL);
}

TEST(MpzCmp, Greater) {
  mpz_t a, b;
  mpz_init_set_ui(a, 100);
  mpz_init_set_ui(b, 42);
  EXPECT_GT(mpz_cmp(a, b), 0);
  mpz_clears(a, b, NULL);
}

TEST(MpzGcd, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 48);
  mpz_init_set_ui(b, 18);
  mpz_init(r);
  mpz_gcd(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 6UL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzLcm, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 4);
  mpz_init_set_ui(b, 6);
  mpz_init(r);
  mpz_lcm(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 12UL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzInvert, Basic) {
  mpz_t a, mod, r;
  mpz_init_set_ui(a, 3);
  mpz_init_set_ui(mod, 11);
  mpz_init(r);
  int res = mpz_invert(r, a, mod);
  EXPECT_EQ(res, 1);
  EXPECT_EQ(mpz_get_ui(r), 4UL);
  mpz_clears(a, mod, r, NULL);
}

TEST(MpzMul2exp, Basic) {
  mpz_t a, r;
  mpz_init_set_ui(a, 1);
  mpz_init(r);
  mpz_mul_2exp(r, a, 10);
  EXPECT_EQ(mpz_get_ui(r), 1024UL);
  mpz_clears(a, r, NULL);
}

TEST(MpzDiv2exp, Basic) {
  mpz_t a, r;
  mpz_init_set_ui(a, 1024);
  mpz_init(r);
  mpz_div_2exp(r, a, 10);
  EXPECT_EQ(mpz_get_ui(r), 1UL);
  mpz_clears(a, r, NULL);
}

TEST(MpzGetStr, Base10) {
  mpz_t a;
  mpz_init_set_ui(a, 12345);
  char* str = mpz_get_str(nullptr, 10, a);
  EXPECT_STREQ(str, "12345");
  free(str);
  mpz_clear(a);
}

TEST(MpzGetStr, Base16) {
  mpz_t a;
  mpz_init_set_ui(a, 255);
  char* str = mpz_get_str(nullptr, 16, a);
  EXPECT_STREQ(str, "ff");
  free(str);
  mpz_clear(a);
}

TEST(MpzAnd, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 0xFF);
  mpz_init_set_ui(b, 0x0F);
  mpz_init(r);
  mpz_and(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 0x0FUL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzOr, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 0xF0);
  mpz_init_set_ui(b, 0x0F);
  mpz_init(r);
  mpz_or(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 0xFFUL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzXor, Basic) {
  mpz_t a, b, r;
  mpz_init_set_ui(a, 0xFF);
  mpz_init_set_ui(b, 0x0F);
  mpz_init(r);
  mpz_xor(r, a, b);
  EXPECT_EQ(mpz_get_ui(r), 0xF0UL);
  mpz_clears(a, b, r, NULL);
}

TEST(MpzPopcount, Basic) {
  mpz_t a;
  mpz_init_set_ui(a, 0xFF);
  EXPECT_EQ(mpz_popcount(a), 8UL);
  mpz_clear(a);
}

TEST(MpzAbs, Basic) {
  mpz_t a, r;
  mpz_init_set_ui(a, 42);
  mpz_neg(a, a);
  mpz_init(r);
  mpz_abs(r, a);
  EXPECT_EQ(mpz_get_si(r), 42L);
  mpz_clears(a, r, NULL);
}