#pragma once

#include <ostream>
#include <string>
#include <utility>

extern "C" {
#include "bigmath/mpz.h"
}

class bigint {
 public:
  bigint() noexcept;
  bigint(int val);
  bigint(unsigned int val);
  bigint(long int val) noexcept;
  bigint(unsigned long int val) noexcept;
  explicit bigint(const std::string& str, int base = 10);

  bigint(const bigint& other) noexcept;
  bigint(bigint&& other) noexcept;
  ~bigint() noexcept;

  bigint& operator=(const bigint& other) noexcept;
  bigint& operator=(bigint&& other) noexcept;
  bigint& operator=(long int val) noexcept;
  bigint& operator=(unsigned long int val) noexcept;

  bigint operator+(const bigint& rhs) const;
  bigint operator-(const bigint& rhs) const;
  bigint operator*(const bigint& rhs) const;
  bigint operator/(const bigint& rhs) const;
  bigint operator%(const bigint& rhs) const;
  bigint operator-() const;

  bigint& operator+=(const bigint& rhs);
  bigint& operator-=(const bigint& rhs);
  bigint& operator*=(const bigint& rhs);
  bigint& operator/=(const bigint& rhs);
  bigint& operator%=(const bigint& rhs);

  bigint operator&(const bigint& rhs) const;
  bigint operator|(const bigint& rhs) const;
  bigint operator^(const bigint& rhs) const;
  bigint operator~() const;
  bigint operator<<(unsigned long int shift) const;
  bigint operator>>(unsigned long int shift) const;

  bigint& operator&=(const bigint& rhs);
  bigint& operator|=(const bigint& rhs);
  bigint& operator^=(const bigint& rhs);
  bigint& operator<<=(unsigned long int shift);
  bigint& operator>>=(unsigned long int shift);

  bool operator==(const bigint& rhs) const;
  bool operator!=(const bigint& rhs) const;
  bool operator<(const bigint& rhs) const;
  bool operator<=(const bigint& rhs) const;
  bool operator>(const bigint& rhs) const;
  bool operator>=(const bigint& rhs) const;

  explicit operator long int() const;
  explicit operator unsigned long int() const;
  explicit operator int() const;
  explicit operator bool() const;

  int sign() const noexcept;

  bigint abs() const;
  bigint negate() const;
  bigint pow(unsigned long int exp) const;
  bigint powm(const bigint& exp, const bigint& mod) const;
  bool invert(bigint& rop, const bigint& mod) const;

  static bigint gcd(const bigint& a, const bigint& b);
  static bigint lcm(const bigint& a, const bigint& b);

  bigint tdiv_q(const bigint& d) const;
  bigint tdiv_r(const bigint& d) const;
  std::pair<bigint, bigint> tdiv_qr(const bigint& d) const;

  bigint fdiv_q(const bigint& d) const;
  bigint fdiv_r(const bigint& d) const;
  std::pair<bigint, bigint> fdiv_qr(const bigint& d) const;

  bigint cdiv_q(const bigint& d) const;
  bigint cdiv_r(const bigint& d) const;
  std::pair<bigint, bigint> cdiv_qr(const bigint& d) const;

  bigint mod(const bigint& d) const;

  unsigned long int popcount() const;
  int scan1(unsigned long int start) const;
  unsigned long int size_in_base(int base) const;
  unsigned long int size() const;

  std::string to_string(int base = 10) const;
  friend std::ostream& operator<<(std::ostream& os, const bigint& x);

  __mpz_struct*       mpz() noexcept;
  const __mpz_struct* mpz() const noexcept;

 private:
  __mpz_struct _z;
};

inline bigint abs(const bigint& a)                                           { return a.abs(); }
inline bigint pow(const bigint& base, unsigned long int exp)                 { return base.pow(exp); }
inline bigint powm(const bigint& base, const bigint& exp, const bigint& mod) { return base.powm(exp, mod); }