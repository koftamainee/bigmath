#include "bigmath/bigint.hpp"

bigint::bigint() noexcept                     { mpz_init(&_z); }
bigint::bigint(int val)                       : bigint((long int)val) {}
bigint::bigint(unsigned int val)              : bigint((unsigned long int)val) {}
bigint::bigint(unsigned long int val) noexcept { mpz_init(&_z); mpz_set_ui(&_z, val); }

bigint::bigint(long int val) noexcept {
  mpz_init(&_z);
  if (val >= 0) mpz_set_ui(&_z, (unsigned long int)val);
  else         { mpz_set_ui(&_z, (unsigned long int)-val); mpz_neg(&_z, &_z); }
}

bigint::bigint(const std::string& str, int base) {
  mpz_init(&_z);
  if (str.empty()) return;
  size_t start = 0;
  bool negative = false;
  if (str[0] == '-') { negative = true; start = 1; }
  mpz_set_ui(&_z, 0);
  for (size_t i = start; i < str.size(); i++) {
    char c = str[i];
    int digit;
    if      (c >= '0' && c <= '9') digit = c - '0';
    else if (c >= 'a' && c <= 'z') digit = c - 'a' + 10;
    else if (c >= 'A' && c <= 'Z') digit = c - 'A' + 10;
    else break;
    mpz_mul_ui(&_z, &_z, (unsigned long int)base);
    mpz_add_ui(&_z, &_z, (unsigned long int)digit);
  }
  if (negative) mpz_neg(&_z, &_z);
}

bigint::bigint(const bigint& other) noexcept { mpz_init_set(&_z, &other._z); }

bigint::bigint(bigint&& other) noexcept {
  _z = other._z;
  mpz_init(&other._z);
}

bigint::~bigint() noexcept { mpz_clear(&_z); }

bigint& bigint::operator=(const bigint& other) noexcept {
  if (this != &other) mpz_set(&_z, &other._z);
  return *this;
}

bigint& bigint::operator=(bigint&& other) noexcept {
  if (this != &other) {
    mpz_clear(&_z);
    _z = other._z;
    mpz_init(&other._z);
  }
  return *this;
}

bigint& bigint::operator=(long int val) noexcept {
  if (val >= 0) mpz_set_ui(&_z, (unsigned long int)val);
  else         { mpz_set_ui(&_z, (unsigned long int)-val); mpz_neg(&_z, &_z); }
  return *this;
}

bigint& bigint::operator=(unsigned long int val) noexcept {
  mpz_set_ui(&_z, val);
  return *this;
}

bigint bigint::operator+(const bigint& rhs) const { bigint r; mpz_add(&r._z, &_z, &rhs._z); return r; }
bigint bigint::operator-(const bigint& rhs) const { bigint r; mpz_sub(&r._z, &_z, &rhs._z); return r; }
bigint bigint::operator*(const bigint& rhs) const { bigint r; mpz_mul(&r._z, &_z, &rhs._z); return r; }
bigint bigint::operator/(const bigint& rhs) const { bigint r; mpz_tdiv_q(&r._z, &_z, &rhs._z); return r; }
bigint bigint::operator%(const bigint& rhs) const { bigint r; mpz_tdiv_r(&r._z, &_z, &rhs._z); return r; }
bigint bigint::operator-()                  const { bigint r(*this); mpz_neg(&r._z, &r._z); return r; }

bigint& bigint::operator+=(const bigint& rhs) { mpz_add(&_z, &_z, &rhs._z); return *this; }
bigint& bigint::operator-=(const bigint& rhs) { mpz_sub(&_z, &_z, &rhs._z); return *this; }
bigint& bigint::operator*=(const bigint& rhs) { mpz_mul(&_z, &_z, &rhs._z); return *this; }
bigint& bigint::operator/=(const bigint& rhs) { mpz_tdiv_q(&_z, &_z, &rhs._z); return *this; }
bigint& bigint::operator%=(const bigint& rhs) { mpz_tdiv_r(&_z, &_z, &rhs._z); return *this; }

bigint bigint::operator&(const bigint& rhs)        const { bigint r; mpz_and(&r._z, &_z, &rhs._z); return r; }
bigint bigint::operator|(const bigint& rhs)        const { bigint r; mpz_or (&r._z, &_z, &rhs._z); return r; }
bigint bigint::operator^(const bigint& rhs)        const { bigint r; mpz_xor(&r._z, &_z, &rhs._z); return r; }
bigint bigint::operator~()                         const { bigint r; mpz_com(&r._z, &_z); return r; }
bigint bigint::operator<<(unsigned long int shift) const { bigint r; mpz_mul_2exp(&r._z, &_z, shift); return r; }
bigint bigint::operator>>(unsigned long int shift) const { bigint r; mpz_div_2exp(&r._z, &_z, shift); return r; }

bigint& bigint::operator&=(const bigint& rhs)        { mpz_and(&_z, &_z, &rhs._z); return *this; }
bigint& bigint::operator|=(const bigint& rhs)        { mpz_or (&_z, &_z, &rhs._z); return *this; }
bigint& bigint::operator^=(const bigint& rhs)        { mpz_xor(&_z, &_z, &rhs._z); return *this; }
bigint& bigint::operator<<=(unsigned long int shift) { mpz_mul_2exp(&_z, &_z, shift); return *this; }
bigint& bigint::operator>>=(unsigned long int shift) { mpz_div_2exp(&_z, &_z, shift); return *this; }

bool bigint::operator==(const bigint& rhs) const { return mpz_cmp(&_z, &rhs._z) == 0; }
bool bigint::operator!=(const bigint& rhs) const { return mpz_cmp(&_z, &rhs._z) != 0; }
bool bigint::operator< (const bigint& rhs) const { return mpz_cmp(&_z, &rhs._z) <  0; }
bool bigint::operator<=(const bigint& rhs) const { return mpz_cmp(&_z, &rhs._z) <= 0; }
bool bigint::operator> (const bigint& rhs) const { return mpz_cmp(&_z, &rhs._z) >  0; }
bool bigint::operator>=(const bigint& rhs) const { return mpz_cmp(&_z, &rhs._z) >= 0; }

bigint::operator long int()          const { return mpz_get_si(&_z); }
bigint::operator unsigned long int() const { return mpz_get_ui(&_z); }
bigint::operator int()               const { return (int)mpz_get_si(&_z); }
bigint::operator bool()              const { return mpz_sgn(&_z) != 0; }

int bigint::sign() const noexcept { return mpz_sgn(&_z); }

bigint bigint::abs()    const { bigint r; mpz_abs(&r._z, &_z); return r; }
bigint bigint::negate() const { bigint r; mpz_neg(&r._z, &_z); return r; }

bigint bigint::pow(unsigned long int exp) const {
  bigint r; mpz_pow_ui(&r._z, &_z, exp); return r;
}

bigint bigint::powm(const bigint& exp, const bigint& mod) const {
  bigint r; mpz_powm(&r._z, &_z, &exp._z, &mod._z); return r;
}

bool bigint::invert(bigint& rop, const bigint& mod) const {
  return mpz_invert(&rop._z, &_z, &mod._z) != 0;
}

bigint bigint::gcd(const bigint& a, const bigint& b) {
  bigint r; mpz_gcd(&r._z, &a._z, &b._z); return r;
}

bigint bigint::lcm(const bigint& a, const bigint& b) {
  bigint r; mpz_lcm(&r._z, &a._z, &b._z); return r;
}

bigint bigint::tdiv_q(const bigint& d) const { bigint r; mpz_tdiv_q(&r._z, &_z, &d._z); return r; }
bigint bigint::tdiv_r(const bigint& d) const { bigint r; mpz_tdiv_r(&r._z, &_z, &d._z); return r; }
std::pair<bigint, bigint> bigint::tdiv_qr(const bigint& d) const {
  bigint q, r; mpz_tdiv_qr(&q._z, &r._z, &_z, &d._z); return {std::move(q), std::move(r)};
}

bigint bigint::fdiv_q(const bigint& d) const { bigint r; mpz_fdiv_q(&r._z, &_z, &d._z); return r; }
bigint bigint::fdiv_r(const bigint& d) const { bigint r; mpz_fdiv_r(&r._z, &_z, &d._z); return r; }
std::pair<bigint, bigint> bigint::fdiv_qr(const bigint& d) const {
  bigint q, r; mpz_fdiv_qr(&q._z, &r._z, &_z, &d._z); return {std::move(q), std::move(r)};
}

bigint bigint::cdiv_q(const bigint& d) const { bigint r; mpz_cdiv_q(&r._z, &_z, &d._z); return r; }
bigint bigint::cdiv_r(const bigint& d) const { bigint r; mpz_cdiv_r(&r._z, &_z, &d._z); return r; }
std::pair<bigint, bigint> bigint::cdiv_qr(const bigint& d) const {
  bigint q, r; mpz_cdiv_qr(&q._z, &r._z, &_z, &d._z); return {std::move(q), std::move(r)};
}

bigint bigint::mod(const bigint& d) const { bigint r; mpz_mod(&r._z, &_z, &d._z); return r; }

unsigned long int bigint::popcount()                  const { return mpz_popcount(&_z); }
int               bigint::scan1(unsigned long int s)  const { return mpz_scan1(&_z, s); }
unsigned long int bigint::size_in_base(int base)      const { return mpz_sizeinbase(&_z, base); }
unsigned long int bigint::size()                      const { return mpz_size(&_z); }

std::string bigint::to_string(int base) const {
  unsigned long int sz = mpz_sizeinbase(&_z, base) + 2;
  char* s = mpz_get_str(nullptr, base, &_z);
  std::string result(s);
  __bigmath_free_func(s, sz);
  return result;
}

std::ostream& operator<<(std::ostream& os, const bigint& x) {
  return os << x.to_string();
}

__mpz_struct*       bigint::mpz() noexcept       { return &_z; }
const __mpz_struct* bigint::mpz() const noexcept { return &_z; }