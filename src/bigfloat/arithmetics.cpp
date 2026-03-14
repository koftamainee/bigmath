#include <utility>

#include "bigmath/bigfloat.hpp"

void bigfloat::simplify() {
  if (numerator_ == 0UL) {
    denominator_ = 1UL;
    return;
  }
  if (numerator_ < 0UL) {
    numerator_.negate();
    denominator_.negate();
  }
  bigint divider = bigint::gcd(numerator_, denominator_.abs());
  if (divider == 1UL) {
    return;
  }
  numerator_ /= divider;
  denominator_ /= divider;
}
bigfloat bigfloat::operator-() const {
  bigfloat negative(*this);
  return bigfloat(negative.negate());
}

bigfloat &bigfloat::negate() {
  denominator_.negate();
  return *this;
}

bigfloat &bigfloat::operator+=(bigfloat const &other) & {
  numerator_ =
      numerator_ * other.denominator_ + other.numerator_ * denominator_;
  denominator_ *= other.denominator_;

  simplify();

  return *this;
}

bigfloat operator+(bigfloat const &first, bigfloat const &second) {
  bigfloat temp(first);
  return bigfloat(temp += second);
}

bigfloat &bigfloat::operator-=(bigfloat const &other) & {
  return *this += -other;
}

bigfloat operator-(bigfloat const &first, bigfloat const &second) {
  return first + -second;
}

bigfloat &bigfloat::operator*=(bigfloat const &other) & {
  numerator_ *= other.numerator_;
  denominator_ *= other.denominator_;
  simplify();
  return *this;
}

bigfloat operator*(bigfloat const &first, bigfloat const &second) {
  bigfloat temp(first);
  return bigfloat(temp *= second);
}

bigfloat &bigfloat::operator/=(bigfloat const &other) & {
  if (other == bigfloat(0UL)) {
    throw std::domain_error("bigfloat: division by zero");
  }
  numerator_ *= other.denominator_;
  denominator_ *= other.numerator_;
  simplify();
  return *this;
}

bigfloat operator/(bigfloat const &first, bigfloat const &second) {
  bigfloat temp(first);
  return bigfloat(temp /= second);
}

bigfloat bigfloat::abs() const { return denominator_ < 0UL ? -*this : bigfloat(*this); }

bigfloat bigfloat::reciprocal() const {
  bigfloat res(denominator_, numerator_);
  if (res.numerator_ < 0L) {
    res.numerator_.negate();
    res.denominator_.negate();
  }
  return bigfloat(res);
}

bigfloat bigfloat::truncate() const { return bigfloat(numerator_ / denominator_, bigint(1UL)); }
