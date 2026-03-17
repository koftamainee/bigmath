#include <gtest/gtest.h>
#include "bigmath/bigint.hpp"

TEST(BigintConstruct, DefaultZero) {
  bigint a;
  EXPECT_EQ(a.sign(), 0);
}

TEST(BigintConstruct, FromInt) {
  bigint a(42);
  EXPECT_EQ((int)a, 42);
}

TEST(BigintConstruct, FromNegativeInt) {
  bigint a(-42);
  EXPECT_EQ((long int)a, -42L);
}

TEST(BigintConstruct, FromUnsignedLong) {
  bigint a(100UL);
  EXPECT_EQ((unsigned long int)a, 100UL);
}

TEST(BigintConstruct, FromString) {
  bigint a("12345");
  EXPECT_EQ(a.to_string(), "12345");
}

TEST(BigintConstruct, FromStringNegative) {
  bigint a("-9999");
  EXPECT_EQ(a.to_string(), "-9999");
}

TEST(BigintConstruct, FromStringHex) {
  bigint a("ff", 16);
  EXPECT_EQ((int)a, 255);
}

TEST(BigintConstruct, CopyCtor) {
  bigint a(123);
  bigint b(a);
  EXPECT_EQ((int)b, 123);
}

TEST(BigintConstruct, MoveCtor) {
  bigint a(123);
  bigint b(std::move(a));
  EXPECT_EQ((int)b, 123);
  EXPECT_EQ(a.sign(), 0);
}

TEST(BigintAssign, CopyAssign) {
  bigint a(10);
  bigint b;
  b = a;
  EXPECT_EQ((int)b, 10);
}

TEST(BigintAssign, MoveAssign) {
  bigint a(10);
  bigint b;
  b = std::move(a);
  EXPECT_EQ((int)b, 10);
  EXPECT_EQ(a.sign(), 0);
}

TEST(BigintAssign, FromLong) {
  bigint a;
  a = -999L;
  EXPECT_EQ((long int)a, -999L);
}

TEST(BigintArith, Add) {
  bigint a(100), b(200);
  EXPECT_EQ((int)(a + b), 300);
}

TEST(BigintArith, AddNegative) {
  bigint a(-100), b(200);
  EXPECT_EQ((int)(a + b), 100);
}

TEST(BigintArith, Sub) {
  bigint a(300), b(100);
  EXPECT_EQ((int)(a - b), 200);
}

TEST(BigintArith, SubNegativeResult) {
  bigint a(100), b(300);
  EXPECT_EQ((long int)(a - b), -200L);
}

TEST(BigintArith, Mul) {
  bigint a(100), b(200);
  EXPECT_EQ((int)(a * b), 20000);
}

TEST(BigintArith, MulNegative) {
  bigint a(-100), b(200);
  EXPECT_EQ((long int)(a * b), -20000L);
}

TEST(BigintArith, Div) {
  bigint a(100), b(7);
  EXPECT_EQ((int)(a / b), 14);
}

TEST(BigintArith, Mod) {
  bigint a(100), b(7);
  EXPECT_EQ((int)(a % b), 2);
}

TEST(BigintArith, UnaryMinus) {
  bigint a(42);
  EXPECT_EQ((long int)(-a), -42L);
}

TEST(BigintArith, AddAssign) {
  bigint a(10);
  a += bigint(5);
  EXPECT_EQ((int)a, 15);
}

TEST(BigintArith, SubAssign) {
  bigint a(10);
  a -= bigint(3);
  EXPECT_EQ((int)a, 7);
}

TEST(BigintArith, MulAssign) {
  bigint a(10);
  a *= bigint(3);
  EXPECT_EQ((int)a, 30);
}

TEST(BigintArith, DivAssign) {
  bigint a(30);
  a /= bigint(3);
  EXPECT_EQ((int)a, 10);
}

TEST(BigintArith, ModAssign) {
  bigint a(17);
  a %= bigint(5);
  EXPECT_EQ((int)a, 2);
}

TEST(BigintCmp, Equal) {
  bigint a(42), b(42);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST(BigintCmp, Less) {
  bigint a(1), b(2);
  EXPECT_TRUE(a < b);
  EXPECT_TRUE(a <= b);
}

TEST(BigintCmp, Greater) {
  bigint a(2), b(1);
  EXPECT_TRUE(a > b);
  EXPECT_TRUE(a >= b);
}

TEST(BigintCmp, NegativeVsPositive) {
  bigint a(-1), b(1);
  EXPECT_TRUE(a < b);
  EXPECT_TRUE(b > a);
}

TEST(BigintBitwise, And) {
  bigint a(0xFF), b(0x0F);
  EXPECT_EQ((int)(a & b), 0x0F);
}

TEST(BigintBitwise, Or) {
  bigint a(0xF0), b(0x0F);
  EXPECT_EQ((int)(a | b), 0xFF);
}

TEST(BigintBitwise, Xor) {
  bigint a(0xFF), b(0x0F);
  EXPECT_EQ((int)(a ^ b), 0xF0);
}

TEST(BigintBitwise, Lshift) {
  bigint a(1);
  EXPECT_EQ((int)(a << 10), 1024);
}

TEST(BigintBitwise, Rshift) {
  bigint a(1024);
  EXPECT_EQ((int)(a >> 10), 1);
}

TEST(BigintBitwise, LshiftAssign) {
  bigint a(1);
  a <<= 8;
  EXPECT_EQ((int)a, 256);
}

TEST(BigintBitwise, RshiftAssign) {
  bigint a(256);
  a >>= 8;
  EXPECT_EQ((int)a, 1);
}

TEST(BigintBitwise, AndAssign) {
  bigint a(0xFF);
  a &= bigint(0x0F);
  EXPECT_EQ((int)a, 0x0F);
}

TEST(BigintBitwise, OrAssign) {
  bigint a(0xF0);
  a |= bigint(0x0F);
  EXPECT_EQ((int)a, 0xFF);
}

TEST(BigintBitwise, XorAssign) {
  bigint a(0xFF);
  a ^= bigint(0x0F);
  EXPECT_EQ((int)a, 0xF0);
}

TEST(BigintBitwise, Popcount) {
  bigint a(0xFF);
  EXPECT_EQ(a.popcount(), 8UL);
}

TEST(BigintBitwise, Scan1) {
  bigint a(0b1010);
  EXPECT_EQ(a.scan1(0), 1);
}

TEST(BigintMath, Abs) {
  bigint a(-42);
  EXPECT_EQ((int)a.abs(), 42);
}

TEST(BigintMath, AbsPositive) {
  bigint a(42);
  EXPECT_EQ((int)a.abs(), 42);
}

TEST(BigintMath, Neg) {
  bigint a(42);
  EXPECT_EQ((long int)a.negate(), -42L);
}

TEST(BigintMath, Pow) {
  bigint a(2);
  EXPECT_EQ((int)a.pow(10), 1024);
}

TEST(BigintMath, PowZero) {
  bigint a(999);
  EXPECT_EQ((int)a.pow(0), 1);
}

TEST(BigintMath, Powm) {
  bigint base(2), exp(10), mod(1000);
  EXPECT_EQ((int)base.powm(exp, mod), 24);
}

TEST(BigintMath, GcdStatic) {
  bigint a(48), b(18);
  EXPECT_EQ((int)bigint::gcd(a, b), 6);
}

TEST(BigintMath, LcmStatic) {
  bigint a(4), b(6);
  EXPECT_EQ((int)bigint::lcm(a, b), 12);
}

TEST(BigintMath, Invert) {
  bigint a(3), mod(11), r;
  EXPECT_TRUE(a.invert(r, mod));
  EXPECT_EQ((int)r, 4);
}

TEST(BigintMath, InvertNoInverse) {
  bigint a(2), mod(4), r;
  EXPECT_FALSE(a.invert(r, mod));
}

TEST(BigintDiv, Tdiv) {
  bigint a(100), b(7);
  auto [q, r] = a.tdiv_qr(b);
  EXPECT_EQ((int)q, 14);
  EXPECT_EQ((int)r, 2);
}

TEST(BigintDiv, Fdiv) {
  bigint a(-7), b(3);
  auto [q, r] = a.fdiv_qr(b);
  EXPECT_EQ((long int)q, -3L);
  EXPECT_EQ((long int)r, 2L);
}

TEST(BigintDiv, Cdiv) {
  bigint a(7), b(3);
  auto [q, r] = a.cdiv_qr(b);
  EXPECT_EQ((int)q, 3);
  EXPECT_EQ((int)r, -2);
}

TEST(BigintDiv, Mod) {
  bigint a(100), b(7);
  EXPECT_EQ((int)a.mod(b), 2);
}

TEST(BigintString, ToStringBase10) {
  bigint a(12345);
  EXPECT_EQ(a.to_string(), "12345");
}

TEST(BigintString, ToStringBase16) {
  bigint a(255);
  EXPECT_EQ(a.to_string(16), "ff");
}

TEST(BigintString, ToStringBase2) {
  bigint a(10);
  EXPECT_EQ(a.to_string(2), "1010");
}

TEST(BigintString, ToStringNegative) {
  bigint a(-42);
  EXPECT_EQ(a.to_string(), "-42");
}

TEST(BigintCast, ToBool) {
  bigint a(0);
  bigint b(1);
  EXPECT_FALSE((bool)a);
  EXPECT_TRUE((bool)b);
}

TEST(BigintInfo, Sign) {
  EXPECT_EQ(bigint(0).sign(), 0);
  EXPECT_EQ(bigint(1).sign(), 1);
  EXPECT_EQ(bigint(-1).sign(), -1);
}

TEST(BigintInfo, Size) {
  bigint a(0);
  bigint b(1);
  EXPECT_EQ(a.size(), 0UL);
  EXPECT_GE(b.size(), 1UL);
}

TEST(BigintInfo, SizeInBase) {
  bigint a(1000);
  EXPECT_GE(a.size_in_base(10), 4UL);
}

TEST(DivisionTest, SmallExact) {
  bigint a(100UL), b(10UL);
  EXPECT_EQ(a / b, bigint(10UL));
  EXPECT_EQ(a % b, bigint(0UL));
}

TEST(DivisionTest, SmallRemainder) {
  bigint a(101UL), b(10UL);
  EXPECT_EQ(a / b, bigint(10UL));
  EXPECT_EQ(a % b, bigint(1UL));
}

TEST(DivisionTest, DivideBySelf) {
  bigint a("99999999999999999999999999999999999999");
  EXPECT_EQ(a / a, bigint(1UL));
  EXPECT_EQ(a % a, bigint(0UL));
}

TEST(DivisionTest, DivideByOne) {
  bigint a("1826487126487612548761256748512876451876518766476125487612586741241");
  EXPECT_EQ(a / bigint(1UL), a);
  EXPECT_EQ(a % bigint(1UL), bigint(0UL));
}

TEST(DivisionTest, ResultIsOne) {
  bigint a("123456789012345678901234567890");
  bigint b("123456789012345678901234567889");
  EXPECT_EQ(a / b, bigint(1UL));
  EXPECT_EQ(a % b, bigint(1UL));
}

TEST(DivisionTest, LargeExact) {
  bigint b("1237812764576145761254124124");
  bigint q("1475576257377699445556752001001338109350");
  bigint a = b * q;
  EXPECT_EQ(a / b, q);
  EXPECT_EQ(a % b, bigint(0UL));
}

TEST(DivisionTest, LargeRemainder) {
  bigint a("1826487126487612548761256748512876451876518766476125487612586741241");
  bigint b("1237812764576145761254124124");
  bigint q = a / b;
  bigint r = a % b;
  EXPECT_EQ(q * b + r, a);
  EXPECT_LT(r, b);
  EXPECT_GE(r, bigint(0UL));
}

TEST(DivisionTest, Factorial1000DivSelf) {
  bigint fact(1UL);
  for (unsigned long int i = 2; i <= 1000; ++i)
    fact *= bigint(i);
  EXPECT_EQ(fact / fact, bigint(1UL));
  EXPECT_EQ(fact % fact, bigint(0UL));
}

TEST(DivisionTest, Factorial1000DivFactor) {
  bigint fact(1UL);
  for (unsigned long int i = 2; i <= 1000; ++i)
    fact *= bigint(i);
  bigint d("9999999999999999999999999999999");
  bigint q = fact / d;
  bigint r = fact % d;
  EXPECT_EQ(q * d + r, fact);
  EXPECT_LT(r, d);
}

TEST(DivisionTest, TdivQR) {
  bigint a("987654321098765432109876543210");
  bigint b("123456789");
  auto [q, r] = a.tdiv_qr(b);
  EXPECT_EQ(q * b + r, a);
  EXPECT_LT(r, b);
}

TEST(DivisionTest, PowerOfTwo) {
  bigint a = bigint(1UL) << 128;
  bigint b = bigint(1UL) << 64;
  EXPECT_EQ(a / b, b);
  EXPECT_EQ(a % b, bigint(0UL));
}

TEST(DivisionTest, NumeratorSmallerThanDenominator) {
  bigint a("123");
  bigint b("99999999999999999999999999999999");
  EXPECT_EQ(a / b, bigint(0UL));
  EXPECT_EQ(a % b, a);
}

TEST(BigintIncrement, PreIncrementPositive) {
  bigint a(41);
  EXPECT_EQ((int)(++a), 42);
  EXPECT_EQ((int)a, 42);
}

TEST(BigintIncrement, PreIncrementNegative) {
  bigint a(-1);
  EXPECT_EQ((int)(++a), 0);
  EXPECT_EQ(a.sign(), 0);
}

TEST(BigintIncrement, PreIncrementZero) {
  bigint a(0);
  EXPECT_EQ((int)(++a), 1);
}

TEST(BigintIncrement, PreIncrementLarge) {
  bigint a("99999999999999999999999999999999999999");
  bigint expected("100000000000000000000000000000000000000");
  ++a;
  EXPECT_EQ(a, expected);
}

TEST(BigintIncrement, PostIncrementReturnsOldValue) {
  bigint a(41);
  bigint old = a++;
  EXPECT_EQ((int)old, 41);
  EXPECT_EQ((int)a, 42);
}

TEST(BigintIncrement, PostIncrementNegative) {
  bigint a(-1);
  bigint old = a++;
  EXPECT_EQ((int)old, -1);
  EXPECT_EQ(a.sign(), 0);
}

TEST(BigintIncrement, PostIncrementLarge) {
  bigint a("99999999999999999999999999999999999999");
  bigint old = a++;
  EXPECT_EQ(old.to_string(), "99999999999999999999999999999999999999");
  EXPECT_EQ(a.to_string(), "100000000000000000000000000000000000000");
}

TEST(BigintDecrement, PreDecrementPositive) {
  bigint a(43);
  EXPECT_EQ((int)(--a), 42);
  EXPECT_EQ((int)a, 42);
}

TEST(BigintDecrement, PreDecrementZero) {
  bigint a(0);
  EXPECT_EQ((int)(--a), -1);
  EXPECT_EQ(a.sign(), -1);
}

TEST(BigintDecrement, PreDecrementNegative) {
  bigint a(-41);
  EXPECT_EQ((long int)(--a), -42L);
}

TEST(BigintDecrement, PreDecrementLarge) {
  bigint a("100000000000000000000000000000000000000");
  bigint expected("99999999999999999999999999999999999999");
  --a;
  EXPECT_EQ(a, expected);
}

TEST(BigintDecrement, PostDecrementReturnsOldValue) {
  bigint a(43);
  bigint old = a--;
  EXPECT_EQ((int)old, 43);
  EXPECT_EQ((int)a, 42);
}

TEST(BigintDecrement, PostDecrementZero) {
  bigint a(0);
  bigint old = a--;
  EXPECT_EQ((int)old, 0);
  EXPECT_EQ(a.sign(), -1);
}

TEST(BigintDecrement, PostDecrementLarge) {
  bigint a("100000000000000000000000000000000000000");
  bigint old = a--;
  EXPECT_EQ(old.to_string(), "100000000000000000000000000000000000000");
  EXPECT_EQ(a.to_string(), "99999999999999999999999999999999999999");
}

TEST(BigintSafeDiv, OperatorDivThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a / z, std::domain_error);
}

TEST(BigintSafeDiv, OperatorModThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a % z, std::domain_error);
}

TEST(BigintSafeDiv, OperatorDivAssignThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a /= z, std::domain_error);
}

TEST(BigintSafeDiv, OperatorModAssignThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a %= z, std::domain_error);
}

TEST(BigintSafeDiv, TdivQThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.tdiv_q(z), std::domain_error);
}

TEST(BigintSafeDiv, TdivRThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.tdiv_r(z), std::domain_error);
}

TEST(BigintSafeDiv, TdivQRThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.tdiv_qr(z), std::domain_error);
}

TEST(BigintSafeDiv, FdivQThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.fdiv_q(z), std::domain_error);
}

TEST(BigintSafeDiv, FdivRThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.fdiv_r(z), std::domain_error);
}

TEST(BigintSafeDiv, FdivQRThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.fdiv_qr(z), std::domain_error);
}

TEST(BigintSafeDiv, CdivQThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.cdiv_q(z), std::domain_error);
}

TEST(BigintSafeDiv, CdivRThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.cdiv_r(z), std::domain_error);
}

TEST(BigintSafeDiv, CdivQRThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.cdiv_qr(z), std::domain_error);
}

TEST(BigintSafeDiv, ModThrowsOnZero) {
  bigint a(100), z(0);
  EXPECT_THROW(a.mod(z), std::domain_error);
}

TEST(BigintSafeDiv, ExceptionMessage) {
  bigint a(1), z(0);
  try {
    a / z;
    FAIL() << "expected std::domain_error";
  } catch (const std::domain_error& e) {
    EXPECT_STREQ(e.what(), "bigint: division by zero");
  }
}

TEST(BigintUnsafeDiv, TdivQUnsafeWorks) {
  bigint a(100), b(7);
  EXPECT_EQ((int)a.tdiv_q_unsafe(b), 14);
}

TEST(BigintUnsafeDiv, TdivRUnsafeWorks) {
  bigint a(100), b(7);
  EXPECT_EQ((int)a.tdiv_r_unsafe(b), 2);
}

TEST(BigintUnsafeDiv, TdivQRUnsafeWorks) {
  bigint a(100), b(7);
  auto [q, r] = a.tdiv_qr_unsafe(b);
  EXPECT_EQ((int)q, 14);
  EXPECT_EQ((int)r, 2);
}

TEST(BigintUnsafeDiv, FdivQUnsafeWorks) {
  bigint a(-7), b(3);
  EXPECT_EQ((long int)a.fdiv_q_unsafe(b), -3L);
}

TEST(BigintUnsafeDiv, FdivRUnsafeWorks) {
  bigint a(-7), b(3);
  EXPECT_EQ((long int)a.fdiv_r_unsafe(b), 2L);
}

TEST(BigintUnsafeDiv, FdivQRUnsafeWorks) {
  bigint a(-7), b(3);
  auto [q, r] = a.fdiv_qr_unsafe(b);
  EXPECT_EQ((long int)q, -3L);
  EXPECT_EQ((long int)r, 2L);
}

TEST(BigintUnsafeDiv, CdivQUnsafeWorks) {
  bigint a(7), b(3);
  EXPECT_EQ((int)a.cdiv_q_unsafe(b), 3);
}

TEST(BigintUnsafeDiv, CdivRUnsafeWorks) {
  bigint a(7), b(3);
  EXPECT_EQ((long int)a.cdiv_r_unsafe(b), -2L);
}

TEST(BigintUnsafeDiv, CdivQRUnsafeWorks) {
  bigint a(7), b(3);
  auto [q, r] = a.cdiv_qr_unsafe(b);
  EXPECT_EQ((int)q, 3);
  EXPECT_EQ((long int)r, -2L);
}

TEST(BigintUnsafeDiv, ModUnsafeWorks) {
  bigint a(100), b(7);
  EXPECT_EQ((int)a.mod_unsafe(b), 2);
}

TEST(BigintCmpUL, EqualUL) {
  bigint a(42UL);
  EXPECT_TRUE(a == 42UL);
  EXPECT_FALSE(a != 42UL);
}

TEST(BigintCmpUL, LessUL) {
  bigint a(5UL);
  EXPECT_TRUE(a < 10UL);
  EXPECT_TRUE(a <= 10UL);
  EXPECT_TRUE(a <= 5UL);
}

TEST(BigintCmpUL, GreaterUL) {
  bigint a(10UL);
  EXPECT_TRUE(a > 5UL);
  EXPECT_TRUE(a >= 5UL);
  EXPECT_TRUE(a >= 10UL);
}

TEST(BigintCmpUL, ZeroUL) {
  bigint a(0UL);
  EXPECT_TRUE(a == 0UL);
  EXPECT_FALSE(a > 0UL);
  EXPECT_FALSE(a < 0UL);
}

TEST(BigintCmpUL, LargeUL) {
  bigint a("99999999999999999999");
  EXPECT_FALSE(a == 99999999999999999UL);
  EXPECT_TRUE(a > 99999999999999999UL);
}

TEST(BigintCmpSL, EqualSL) {
  bigint a(-42L);
  EXPECT_TRUE(a == -42L);
  EXPECT_FALSE(a != -42L);
}

TEST(BigintCmpSL, LessSL) {
  bigint a(-10);
  EXPECT_TRUE(a < -5L);
  EXPECT_TRUE(a <= -5L);
  EXPECT_TRUE(a <= -10L);
}

TEST(BigintCmpSL, GreaterSL) {
  bigint a(10);
  EXPECT_TRUE(a > -1L);
  EXPECT_TRUE(a >= -1L);
  EXPECT_TRUE(a >= 10L);
}

TEST(BigintCmpSL, ZeroSL) {
  bigint a(0);
  EXPECT_TRUE(a == 0L);
  EXPECT_FALSE(a > 0L);
  EXPECT_FALSE(a < 0L);
}

TEST(BigintCmpSL, NegativeVsPositiveSL) {
  bigint a(-1);
  EXPECT_TRUE(a < 1L);
  EXPECT_FALSE(a > 0L);
}

TEST(BigintArithUL, AddUL) {
  bigint a(100UL);
  EXPECT_EQ((unsigned long int)(a + 200UL), 300UL);
}

TEST(BigintArithUL, AddULZero) {
  bigint a(42UL);
  EXPECT_EQ((unsigned long int)(a + 0UL), 42UL);
}

TEST(BigintArithUL, SubUL) {
  bigint a(300UL);
  EXPECT_EQ((unsigned long int)(a - 100UL), 200UL);
}

TEST(BigintArithUL, SubULToZero) {
  bigint a(42UL);
  EXPECT_EQ((unsigned long int)(a - 42UL), 0UL);
}

TEST(BigintArithUL, SubULNegativeResult) {
  bigint a(5UL);
  bigint r = a - 10UL;
  EXPECT_EQ(r.sign(), -1);
  EXPECT_EQ((long int)r, -5L);
}

TEST(BigintArithUL, MulUL) {
  bigint a(100UL);
  EXPECT_EQ((unsigned long int)(a * 200UL), 20000UL);
}

TEST(BigintArithUL, MulULZero) {
  bigint a(99999UL);
  EXPECT_EQ((unsigned long int)(a * 0UL), 0UL);
}

TEST(BigintArithUL, MulULOne) {
  bigint a(12345UL);
  EXPECT_EQ((unsigned long int)(a * 1UL), 12345UL);
}

TEST(BigintArithUL, MulULLarge) {
  bigint a("999999999999999999999999999999");
  bigint r = a * 2UL;
  EXPECT_EQ(r.to_string(), "1999999999999999999999999999998");
}

TEST(BigintArithAssignUL, AddAssignUL) {
  bigint a(10UL);
  a += 5UL;
  EXPECT_EQ((unsigned long int)a, 15UL);
}

TEST(BigintArithAssignUL, AddAssignULZero) {
  bigint a(42UL);
  a += 0UL;
  EXPECT_EQ((unsigned long int)a, 42UL);
}

TEST(BigintArithAssignUL, AddAssignULLarge) {
  bigint a("999999999999999999999999999999");
  a += 1UL;
  EXPECT_EQ(a.to_string(), "1000000000000000000000000000000");
}

TEST(BigintArithAssignUL, SubAssignUL) {
  bigint a(10UL);
  a -= 3UL;
  EXPECT_EQ((unsigned long int)a, 7UL);
}

TEST(BigintArithAssignUL, SubAssignULToZero) {
  bigint a(5UL);
  a -= 5UL;
  EXPECT_EQ(a.sign(), 0);
}

TEST(BigintArithAssignUL, SubAssignULNegativeResult) {
  bigint a(3UL);
  a -= 10UL;
  EXPECT_EQ((long int)a, -7L);
}

TEST(BigintArithAssignUL, MulAssignUL) {
  bigint a(10UL);
  a *= 3UL;
  EXPECT_EQ((unsigned long int)a, 30UL);
}

TEST(BigintArithAssignUL, MulAssignULZero) {
  bigint a(99999UL);
  a *= 0UL;
  EXPECT_EQ(a.sign(), 0);
}

TEST(BigintArithAssignUL, MulAssignULOne) {
  bigint a(12345UL);
  a *= 1UL;
  EXPECT_EQ((unsigned long int)a, 12345UL);
}

TEST(BigintArithAssignUL, MulAssignULLarge) {
  bigint a("999999999999999999999999999999");
  a *= 2UL;
  EXPECT_EQ(a.to_string(), "1999999999999999999999999999998");
}

TEST(BigintNegate, NegatePositive) {
  bigint a(42);
  a.negate();
  EXPECT_EQ((long int)a, -42L);
}

TEST(BigintNegate, NegateNegative) {
  bigint a(-42);
  a.negate();
  EXPECT_EQ((int)a, 42);
}

TEST(BigintNegate, NegateZero) {
  bigint a(0);
  a.negate();
  EXPECT_EQ(a.sign(), 0);
}

TEST(BigintNegate, NegateChain) {
  bigint a(10);
  a.negate().negate();
  EXPECT_EQ((int)a, 10);
}

TEST(BigintNegate, NegateReturnsRef) {
  bigint a(5);
  bigint& r = a.negate();
  EXPECT_EQ(&r, &a);
}

TEST(BigintBitInverse, InversePositive) {
  bigint a(0);
  a.bit_inverse();
  EXPECT_EQ((long int)a, -1L);
}

TEST(BigintBitInverse, InverseNegOne) {
  bigint a(-1);
  a.bit_inverse();
  EXPECT_EQ((int)a, 0);
}

TEST(BigintBitInverse, InverseDouble) {
  bigint a(42);
  a.bit_inverse().bit_inverse();
  EXPECT_EQ((int)a, 42);
}

TEST(BigintBitInverse, InverseReturnsRef) {
  bigint a(1);
  bigint& r = a.bit_inverse();
  EXPECT_EQ(&r, &a);
}

TEST(BigintBitInverse, InverseMatchesTilde) {
  bigint a(0xFF);
  bigint b(0xFF);
  a.bit_inverse();
  EXPECT_EQ(a, ~b);
}

TEST(BigintFactorial, FactorialULZero) {
  EXPECT_EQ((int)bigint::factorial(0UL), 1);
}

TEST(BigintFactorial, FactorialULOne) {
  EXPECT_EQ((int)bigint::factorial(1UL), 1);
}

TEST(BigintFactorial, FactorialULSmall) {
  EXPECT_EQ((int)bigint::factorial(5UL), 120);
}

TEST(BigintFactorial, FactorialUL10) {
  EXPECT_EQ((int)bigint::factorial(10UL), 3628800);
}

TEST(BigintFactorial, FactorialULLarge) {
  bigint r = bigint::factorial(20UL);
  EXPECT_EQ(r.to_string(), "2432902008176640000");
}

TEST(BigintFactorial, FactorialBigintZero) {
  EXPECT_EQ((int)bigint::factorial(bigint(0)), 1);
}

TEST(BigintFactorial, FactorialBigintSmall) {
  EXPECT_EQ((int)bigint::factorial(bigint(5)), 120);
}

TEST(BigintFactorial, FactorialBigintMatchesUL) {
  EXPECT_EQ(bigint::factorial(bigint(15)), bigint::factorial(15UL));
}

TEST(BigintFactorial, FactorialBigintNegativeThrows) {
  EXPECT_THROW(bigint::factorial(bigint(-1)), std::domain_error);
}

TEST(BigintRandRange, Basic) {
  const bigint random = bigint::rand_range(bigint("12345"), bigint("67890"));
  EXPECT_TRUE(random < bigint("67890"));
  EXPECT_TRUE(random >= bigint("12345"));
}