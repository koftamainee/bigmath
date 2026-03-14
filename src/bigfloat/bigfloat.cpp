#include "bigmath/bigfloat.hpp"

#include <stdexcept>

const bigfloat bigfloat::DEFAULT_EPS = bigfloat(bigint(1), bigint(1000000));

std::map<bigfloat, bigfloat> bigfloat::pi_cache_;
std::vector<bigfloat> bigfloat::bernoulli_cache_ = {1, bigfloat(bigint(-1), bigint(2))};

bigfloat::bigfloat() {
  numerator_ = bigint(0);
  denominator_ = bigint(1);
}

bigfloat::bigfloat(long int other) : numerator_(static_cast<long int>(other)), denominator_(1) {}

bigfloat::bigfloat(unsigned long int other) : numerator_(static_cast<unsigned long int>(other)), denominator_(1) {}

bigfloat::bigfloat(bigint const &numerator, bigint const &denominator) {
  if (denominator == bigint(0)) {
    throw std::invalid_argument("Denominator can not be 0");
  }
  if (numerator >= bigint(0) && denominator >= bigint(0)) {
    numerator_ = numerator;
    denominator_ = denominator;
  } else if (numerator < bigint(0) || denominator < bigint(0)) {
    numerator_ = -numerator;
    denominator_ = -denominator;
  } else {
    numerator_ = numerator.abs();
    denominator_ = denominator < 0L ? denominator : -denominator;
  }
  simplify();
}

bigfloat::bigfloat(bigint const &other)
    : numerator_(other.abs()), denominator_(other < bigint(0) ? bigint(-1) : bigint(1)) {}

bigfloat::bigfloat(int other) : numerator_(static_cast<long int>(other)), denominator_(1UL) {}