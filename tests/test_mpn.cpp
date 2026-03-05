#include <gtest/gtest.h>

extern "C" {
#include "bigmath/mpn.h"
}

TEST(MpnAddN, Basic) {
  mp_limb_t x[] = {0xFFFFFFFFFFFFFFFF};
  mp_limb_t y[] = {1};
  mp_limb_t r[1];
  mp_limb_t carry = mpn_add_n(r, x, y, 1);
  EXPECT_EQ(r[0], 0UL);
  EXPECT_EQ(carry, 1UL);
}

TEST(MpnAddN, NoCarry) {
  mp_limb_t x[] = {1, 2};
  mp_limb_t y[] = {3, 4};
  mp_limb_t r[2];
  mp_limb_t carry = mpn_add_n(r, x, y, 2);
  EXPECT_EQ(r[0], 4UL);
  EXPECT_EQ(r[1], 6UL);
  EXPECT_EQ(carry, 0UL);
}

TEST(MpnSubN, Basic) {
  mp_limb_t x[] = {5};
  mp_limb_t y[] = {3};
  mp_limb_t r[1];
  mp_limb_t borrow = mpn_sub_n(r, x, y, 1);
  EXPECT_EQ(r[0], 2UL);
  EXPECT_EQ(borrow, 0UL);
}

TEST(MpnSubN, Borrow) {
  mp_limb_t x[] = {0};
  mp_limb_t y[] = {1};
  mp_limb_t r[1];
  mp_limb_t borrow = mpn_sub_n(r, x, y, 1);
  EXPECT_EQ(r[0], 0xFFFFFFFFFFFFFFFFUL);
  EXPECT_EQ(borrow, 1UL);
}

TEST(MpnAdd, DifferentSizes) {
  mp_limb_t x[] = {0xFFFFFFFFFFFFFFFF, 1};
  mp_limb_t y[] = {1};
  mp_limb_t r[3] = {0};
  mp_limb_t carry = mpn_add(r, x, 2, y, 1);
  EXPECT_EQ(r[0], 0UL);
  EXPECT_EQ(r[1], 2UL);
  EXPECT_EQ(carry, 0UL);
}

TEST(MpnCmp, Equal) {
  mp_limb_t x[] = {1, 2, 3};
  mp_limb_t y[] = {1, 2, 3};
  EXPECT_EQ(mpn_cmp(x, y, 3), 0);
}

TEST(MpnCmp, Greater) {
  mp_limb_t x[] = {1, 3};
  mp_limb_t y[] = {1, 2};
  EXPECT_GT(mpn_cmp(x, y, 2), 0);
}

TEST(MpnCmp, Less) {
  mp_limb_t x[] = {1, 2};
  mp_limb_t y[] = {1, 3};
  EXPECT_LT(mpn_cmp(x, y, 2), 0);
}

TEST(MpnMul1, Basic) {
  mp_limb_t x[] = {100};
  mp_limb_t r[1];
  mp_limb_t carry = mpn_mul_1(r, x, 1, 3);
  EXPECT_EQ(r[0], 300UL);
  EXPECT_EQ(carry, 0UL);
}

TEST(MpnMul1, Zero) {
  mp_limb_t x[] = {100, 200};
  mp_limb_t r[2];
  mp_limb_t carry = mpn_mul_1(r, x, 2, 0);
  EXPECT_EQ(r[0], 0UL);
  EXPECT_EQ(r[1], 0UL);
  EXPECT_EQ(carry, 0UL);
}

TEST(MpnMul, Basic) {
  mp_limb_t x[] = {100};
  mp_limb_t y[] = {200};
  mp_limb_t r[2] = {0};
  mpn_mul(r, x, 1, y, 1);
  EXPECT_EQ(r[0], 20000UL);
  EXPECT_EQ(r[1], 0UL);
}

TEST(MpnLshift, Basic) {
  mp_limb_t x[] = {1};
  mp_limb_t r[1];
  mp_limb_t carry = mpn_lshift(r, x, 1, 4);
  EXPECT_EQ(r[0], 16UL);
  EXPECT_EQ(carry, 0UL);
}

TEST(MpnLshift, WithCarry) {
  mp_limb_t x[] = {0x8000000000000000UL};
  mp_limb_t r[1];
  mp_limb_t carry = mpn_lshift(r, x, 1, 1);
  EXPECT_EQ(r[0], 0UL);
  EXPECT_EQ(carry, 1UL);
}

TEST(MpnRshift, Basic) {
  mp_limb_t x[] = {16};
  mp_limb_t r[1];
  mp_limb_t carry = mpn_rshift(r, x, 1, 4);
  EXPECT_EQ(r[0], 1UL);
  EXPECT_EQ(carry, 0UL);
}

TEST(MpnPopcount, Basic) {
  mp_limb_t x[] = {0xFF};
  EXPECT_EQ(mpn_popcount(x, 1), 8UL);
}

TEST(MpnPopcount, Zero) {
  mp_limb_t x[] = {0};
  EXPECT_EQ(mpn_popcount(x, 1), 0UL);
}

TEST(MpnAndN, Basic) {
  mp_limb_t x[] = {0xFF};
  mp_limb_t y[] = {0x0F};
  mp_limb_t r[1];
  mpn_and_n(r, x, y, 1);
  EXPECT_EQ(r[0], 0x0FUL);
}

TEST(MpnIorN, Basic) {
  mp_limb_t x[] = {0xF0};
  mp_limb_t y[] = {0x0F};
  mp_limb_t r[1];
  mpn_ior_n(r, x, y, 1);
  EXPECT_EQ(r[0], 0xFFUL);
}

TEST(MpnXorN, Basic) {
  mp_limb_t x[] = {0xFF};
  mp_limb_t y[] = {0x0F};
  mp_limb_t r[1];
  mpn_xor_n(r, x, y, 1);
  EXPECT_EQ(r[0], 0xF0UL);
}

TEST(MpnComN, Basic) {
  mp_limb_t x[] = {0};
  mp_limb_t r[1];
  mpn_com_n(r, x, 1);
  EXPECT_EQ(r[0], 0xFFFFFFFFFFFFFFFFUL);
}

TEST(MpnScan1, Basic) {
  mp_limb_t x[] = {0b1010};
  EXPECT_EQ(mpn_scan1(x, 1, 0), 1UL);
}

TEST(MpnScan1, StartMid) {
  mp_limb_t x[] = {0b1010};
  EXPECT_EQ(mpn_scan1(x, 1, 2), 3UL);
}