#include <stdexcept>

#include "bigmath/bigfloat.hpp"

bigfloat pow(bigfloat const &base, bigint const &exp) {
  if (exp == 0UL) {
    return bigfloat(1UL);
  }
  if (exp < 0UL) {
    return bigfloat(1UL) / pow(base, -exp);
  }
  bigfloat result(1UL);
  bigfloat x(base);
  bigint n = exp;

  while (n > 0UL) {
    if (n & bigint(1)) {
      result *= x;
    }
    x *= x;
    n = n / bigint(2);
  }

  return bigfloat(result);
}

bigfloat radical(const bigfloat &radicand, const bigint &index,
                 const bigfloat &EPS) {
  if (index == 0UL) {
    throw std::invalid_argument("Index cannot be zero!");
  }
  if (radicand < bigfloat(0UL) && (index % bigint(2) == 0UL)) {
    throw std::invalid_argument("Negative radicand with even index");
  }

  bigfloat approx(1UL);
  while (pow(approx, index) < radicand.abs()) {
    approx *= bigfloat(2UL);
  }
  bigfloat x = (radicand < bigfloat(0UL)) ? -approx : bigfloat(approx);

  bigfloat delta;

  do {
    bigfloat x_prev(x);

    bigfloat x_to_power(1UL);
    for (bigint i(0UL); i < index - 1; ++i) {
      x_to_power *= x;
    }

    x = (bigfloat(index - 1) * x + radicand / x_to_power) / bigfloat(index);

    delta = (x - x_prev).abs();
  } while (delta > EPS);

  return bigfloat(x);
}

bigfloat sqrt(bigfloat const &radicand, bigfloat const &EPS) {
  return radical(radicand, bigint(2UL), EPS);
}
