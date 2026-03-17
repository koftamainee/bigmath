#include <gtest/gtest.h>
#include "bigmath/mpz.h"
#include "bigmath/defines.h"
#include <string>

static std::string mpz_to_str(mpz_srcptr x) {
    char* buf = mpz_get_str(nullptr, 10, x);
    std::string s(buf);
    free(buf);
    return s;
}

static void mpz_set_str10(mpz_ptr x, const char* s) {
    mpz_set_ui(x, 0);
    int neg = 0;
    if (*s == '-') { neg = 1; ++s; }
    for (; *s; ++s) {
        mpz_mul_ui(x, x, 10);
        mpz_add_ui(x, x, (unsigned)(*s - '0'));
    }
    if (neg) mpz_neg(x, x);
}

// Macro: assert mpz result equals a decimal string
#define EXPECT_MPZ_EQ(op, expected_str)          \
    do {                                         \
        EXPECT_EQ(mpz_to_str(op), expected_str); \
    } while (0)

class MpzOpsTest : public ::testing::Test {
protected:
    mpz_t a, b, na, rop, q, r;

    // Test values
    // a  =  123456789012345678901234567890
    // b  =  987654321098765432109876543210
    // na = -123456789012345678901234567890
    static constexpr const char* A_STR  =  "123456789012345678901234567890";
    static constexpr const char* B_STR  =  "987654321098765432109876543210";
    static constexpr const char* NA_STR = "-123456789012345678901234567890";

    void SetUp() override {
        mpz_inits(a, b, na, rop, q, r, nullptr);
        mpz_set_str10(a,  A_STR);
        mpz_set_str10(b,  B_STR);
        mpz_set_str10(na, NA_STR);
    }

    void TearDown() override {
        mpz_clears(a, b, na, rop, q, r, nullptr);
    }
};

TEST_F(MpzOpsTest, InitSetGet) {
    EXPECT_MPZ_EQ(a,  A_STR);
    EXPECT_MPZ_EQ(b,  B_STR);
    EXPECT_MPZ_EQ(na, NA_STR);
}

TEST_F(MpzOpsTest, SetUi) {
    mpz_set_ui(rop, 999999999UL);
    EXPECT_MPZ_EQ(rop, "999999999");
}

TEST_F(MpzOpsTest, GetUi) {
    unsigned long val = mpz_get_ui(a);
    EXPECT_EQ(val, 14083847773837265618UL);
}

TEST_F(MpzOpsTest, GetSi) {
    mpz_t x;
    mpz_init(x);
    mpz_set_str10(x, "-9223372036854775808");
    long val = mpz_get_si(x);
    EXPECT_EQ(val, -9223372036854775808ULL);
    mpz_clear(x);
}

TEST_F(MpzOpsTest, Add) {
    mpz_add(rop, a, b);
    EXPECT_MPZ_EQ(rop, "1111111110111111111011111111100");
}

TEST_F(MpzOpsTest, Sub) {
    mpz_sub(rop, a, b);
    EXPECT_MPZ_EQ(rop, "-864197532086419753208641975320");
}

TEST_F(MpzOpsTest, Mul) {
    mpz_mul(rop, a, b);
    EXPECT_MPZ_EQ(rop,
        "121932631137021795226185032733622923332237463801111263526900");
}

TEST_F(MpzOpsTest, AddUi) {
    mpz_add_ui(rop, a, 999999999UL);
    EXPECT_MPZ_EQ(rop, "123456789012345678902234567889");
}

TEST_F(MpzOpsTest, SubUi) {
    mpz_sub_ui(rop, a, 999999999UL);
    EXPECT_MPZ_EQ(rop, "123456789012345678900234567891");
}

TEST_F(MpzOpsTest, MulUi) {
    mpz_mul_ui(rop, a, 999999999UL);
    EXPECT_MPZ_EQ(rop, "123456788888888889888888888988765432110");
}

TEST_F(MpzOpsTest, TdivQ_AltB) {
    mpz_tdiv_q(q, a, b);
    EXPECT_MPZ_EQ(q, "0");
}

TEST_F(MpzOpsTest, TdivR_AltB) {
    mpz_tdiv_r(r, a, b);
    EXPECT_MPZ_EQ(r, A_STR);
}

TEST_F(MpzOpsTest, TdivQR_AgtB) {
    mpz_tdiv_qr(q, r, b, a);
    EXPECT_MPZ_EQ(q, "8");
    EXPECT_MPZ_EQ(r, "9000000000900000000090");
}

TEST_F(MpzOpsTest, TdivQ_Negative) {
    mpz_tdiv_q(q, na, b);
    EXPECT_MPZ_EQ(q, "0");
}

TEST_F(MpzOpsTest, TdivR_Negative) {
    mpz_tdiv_r(r, na, b);
    EXPECT_MPZ_EQ(r, NA_STR);
}

TEST_F(MpzOpsTest, FdivQ_AltB) {
    mpz_fdiv_q(q, a, b);
    EXPECT_MPZ_EQ(q, "0");
}

TEST_F(MpzOpsTest, FdivR_AltB) {
    mpz_fdiv_r(r, a, b);
    EXPECT_MPZ_EQ(r, A_STR);
}

TEST_F(MpzOpsTest, FdivQR_AgtB) {
    mpz_fdiv_qr(q, r, b, a);
    EXPECT_MPZ_EQ(q, "8");
    EXPECT_MPZ_EQ(r, "9000000000900000000090");
}

TEST_F(MpzOpsTest, FdivQ_Negative) {
    mpz_fdiv_q(q, na, b);
    EXPECT_MPZ_EQ(q, "-1");
}

TEST_F(MpzOpsTest, FdivR_Negative) {
    mpz_fdiv_r(r, na, b);
    EXPECT_MPZ_EQ(r, "864197532086419753208641975320");
}

TEST_F(MpzOpsTest, FdivQR_Negative) {
    mpz_fdiv_qr(q, r, na, b);
    EXPECT_MPZ_EQ(q, "-1");
    EXPECT_MPZ_EQ(r, "864197532086419753208641975320");
}

TEST_F(MpzOpsTest, CdivQ_AltB) {
    mpz_cdiv_q(q, a, b);
    EXPECT_MPZ_EQ(q, "1");
}

TEST_F(MpzOpsTest, CdivR_AltB) {
    mpz_cdiv_r(r, a, b);
    EXPECT_MPZ_EQ(r, "-864197532086419753208641975320");
}

TEST_F(MpzOpsTest, CdivQR_AltB) {
    mpz_cdiv_qr(q, r, a, b);
    EXPECT_MPZ_EQ(q, "1");
    EXPECT_MPZ_EQ(r, "-864197532086419753208641975320");
}

TEST_F(MpzOpsTest, CdivQ_Negative) {
    mpz_cdiv_q(q, na, b);
    EXPECT_MPZ_EQ(q, "0");
}

TEST_F(MpzOpsTest, CdivR_Negative) {
    mpz_cdiv_r(r, na, b);
    EXPECT_MPZ_EQ(r, NA_STR);
}

TEST_F(MpzOpsTest, Mod) {
    mpz_mod(rop, a, b);
    EXPECT_MPZ_EQ(rop, A_STR);
}

TEST_F(MpzOpsTest, Mod_BgtA) {
    mpz_mod(rop, b, a);
    EXPECT_MPZ_EQ(rop, "9000000000900000000090");
}

TEST_F(MpzOpsTest, PowUi) {
    mpz_pow_ui(rop, a, 3UL);
    EXPECT_MPZ_EQ(rop,
        "1881676372353657772546716040589641726257477229849409426207693797722198701224860897069000");
}

TEST_F(MpzOpsTest, PowUi_Zero) {
    mpz_pow_ui(rop, a, 0UL);
    EXPECT_MPZ_EQ(rop, "1");
}

TEST_F(MpzOpsTest, PowUi_One) {
    mpz_pow_ui(rop, a, 1UL);
    EXPECT_MPZ_EQ(rop, A_STR);
}

TEST_F(MpzOpsTest, Powm) {
    mpz_t mod;
    mpz_init(mod);
    mpz_set_str10(mod, "999999999999999999999999999999");
    mpz_t exp3;
    mpz_init_set_ui(exp3, 3UL);
    mpz_powm(rop, a, exp3, mod);
    EXPECT_MPZ_EQ(rop, "285321124828532112482853211248");
    mpz_clears(mod, exp3, nullptr);
}

TEST_F(MpzOpsTest, Mul2Exp) {
    mpz_mul_2exp(rop, a, 17);
    EXPECT_MPZ_EQ(rop, "16181728249426172824942617282478080");
}

TEST_F(MpzOpsTest, Div2Exp) {
    mpz_div_2exp(rop, a, 17);
    EXPECT_MPZ_EQ(rop, "941900550936475211343647");
}

TEST_F(MpzOpsTest, Div2Exp_Zero) {
    mpz_div_2exp(rop, a, 0);
    EXPECT_MPZ_EQ(rop, A_STR);
}

TEST_F(MpzOpsTest, Div2Exp_LargeShift) {
    mpz_div_2exp(rop, a, 200);
    EXPECT_MPZ_EQ(rop, "0");
}

TEST_F(MpzOpsTest, Cmp_AltB) {
    EXPECT_LT(mpz_cmp(a, b), 0);
}

TEST_F(MpzOpsTest, Cmp_Equal) {
    mpz_t x;
    mpz_init_set(x, a);
    EXPECT_EQ(mpz_cmp(a, x), 0);
    mpz_clear(x);
}

TEST_F(MpzOpsTest, Cmp_AgtB) {
    EXPECT_GT(mpz_cmp(b, a), 0);
}

TEST_F(MpzOpsTest, CmpUi) {
    mpz_t small;
    mpz_init_set_ui(small, 42UL);
    EXPECT_GT(mpz_cmp_ui(a, 42UL), 0);
    EXPECT_EQ(mpz_cmp_ui(small, 42UL), 0);
    mpz_clear(small);
}

TEST_F(MpzOpsTest, CmpSi_Negative) {
    EXPECT_LT(mpz_cmp_si(na, 0L), 0);
    EXPECT_GT(mpz_cmp_si(a, -1L), 0);
}

TEST_F(MpzOpsTest, Cmpabs) {
    EXPECT_LT(mpz_cmpabs(a, b), 0);
    EXPECT_EQ(mpz_cmpabs(a, na), 0);
}

TEST_F(MpzOpsTest, Sgn_Positive) {
    EXPECT_EQ(mpz_sgn(a), 1);
}

TEST_F(MpzOpsTest, Sgn_Negative) {
    EXPECT_EQ(mpz_sgn(na), -1);
}

TEST_F(MpzOpsTest, Sgn_Zero) {
    mpz_t zero;
    mpz_init(zero);
    EXPECT_EQ(mpz_sgn(zero), 0);
    mpz_clear(zero);
}

TEST_F(MpzOpsTest, And) {
    mpz_and(rop, a, b);
    EXPECT_MPZ_EQ(rop, "1943960184490269435062782658");
}

TEST_F(MpzOpsTest, Or) {
    mpz_or(rop, a, b);
    EXPECT_MPZ_EQ(rop, "1109167149926620841576048328442");
}

TEST_F(MpzOpsTest, Xor) {
    mpz_xor(rop, a, b);
    EXPECT_MPZ_EQ(rop, "1107223189742130572140985545784");
}

TEST_F(MpzOpsTest, Com) {
    mpz_com(rop, a);
    mpz_t expected;
    mpz_init(expected);
    mpz_set_str10(expected, "-123456789012345678901234567891");
    EXPECT_EQ(mpz_cmp(rop, expected), 0);
    mpz_clear(expected);
}

TEST_F(MpzOpsTest, Popcount) {
    EXPECT_EQ(mpz_popcount(a), 54UL);
}

TEST_F(MpzOpsTest, Scan1) {
    EXPECT_EQ(mpz_scan1(a, 0), 1);
}

TEST_F(MpzOpsTest, Size) {
    EXPECT_EQ(mpz_size(a), 2UL);
}

TEST_F(MpzOpsTest, SizeinbaseDecimal) {
    EXPECT_EQ(mpz_sizeinbase(a, 10), 30UL);
}

TEST_F(MpzOpsTest, SizeinbaseBinary) {
    EXPECT_EQ(mpz_sizeinbase(a, 2), 97UL);
}

TEST_F(MpzOpsTest, GetStr) {
    char* s = mpz_get_str(nullptr, 10, a);
    EXPECT_STREQ(s, A_STR);
    free(s);
}

TEST_F(MpzOpsTest, GetStrNeg) {
    char* s = mpz_get_str(nullptr, 10, na);
    EXPECT_STREQ(s, NA_STR);
    free(s);
}

TEST_F(MpzOpsTest, Gcd) {
    mpz_gcd(rop, a, b);
    EXPECT_MPZ_EQ(rop, "9000000000900000000090");
}

TEST_F(MpzOpsTest, Lcm) {
    mpz_lcm(rop, a, b);
    EXPECT_MPZ_EQ(rop, "13548070124980948012498094801236261410");
}

TEST_F(MpzOpsTest, Neg) {
    mpz_neg(rop, a);
    EXPECT_MPZ_EQ(rop, NA_STR);
}

TEST_F(MpzOpsTest, NegOfNeg) {
    mpz_neg(rop, na);
    EXPECT_MPZ_EQ(rop, A_STR);
}

TEST_F(MpzOpsTest, Abs) {
    mpz_abs(rop, na);
    EXPECT_MPZ_EQ(rop, A_STR);
}

TEST_F(MpzOpsTest, AbsPositive) {
    mpz_abs(rop, a);
    EXPECT_MPZ_EQ(rop, A_STR);
}

TEST_F(MpzOpsTest, AddZero) {
    mpz_t zero;
    mpz_init(zero);
    mpz_add(rop, a, zero);
    EXPECT_MPZ_EQ(rop, A_STR);
    mpz_clear(zero);
}

TEST_F(MpzOpsTest, MulZero) {
    mpz_t zero;
    mpz_init(zero);
    mpz_mul(rop, a, zero);
    EXPECT_MPZ_EQ(rop, "0");
    mpz_clear(zero);
}

TEST_F(MpzOpsTest, SubSelf) {
    mpz_sub(rop, a, a);
    EXPECT_MPZ_EQ(rop, "0");
}

TEST_F(MpzOpsTest, TdivQ_SelfDivSelf) {
    mpz_tdiv_q(q, a, a);
    EXPECT_MPZ_EQ(q, "1");
}

TEST_F(MpzOpsTest, Mul2Exp_Zero) {
    mpz_mul_2exp(rop, a, 0);
    EXPECT_MPZ_EQ(rop, A_STR);
}