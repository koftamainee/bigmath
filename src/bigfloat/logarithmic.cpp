#include <stdexcept>

#include "bigmath/bigfloat.hpp"

bigfloat log_taylor_series(const bigfloat &x, const bigfloat &EPS) {
  bigfloat w = (x - bigfloat(1UL)) / (x + bigfloat(1UL));
  bigfloat w_squared = w * w;
  bigfloat term(w);
  bigfloat result(w);
  bigfloat n = bigfloat(3UL);

  while (term.abs() > EPS) {
    term *= w_squared;
    result += term / n;
    n += bigfloat(2UL);
  }

  return result * bigfloat(2UL);
}

bigfloat log(bigfloat const &number, bigfloat const &EPS) {
  if (number <= bigfloat(0UL)) {
    throw std::invalid_argument("logarithm of non-positive number");
  }

  bigfloat x(number);
  bigint k(0UL);

  while (x > bigfloat(1UL)) {
    x /= bigfloat(2UL);
    ++k;
  }
  while (x < bigfloat(bigint(1UL), bigint(2UL))) {
    x *= bigfloat(2UL);
    --k;
  }

  static bigfloat ln2 = log_taylor_series(bigfloat(2UL), EPS);
  return log_taylor_series(x, EPS) + bigfloat(k) * ln2;
}

bigfloat log2(bigfloat const &number, bigfloat const &EPS) {
  bigfloat ln2 = log(bigfloat(2UL), EPS);
  return log(number, EPS) / ln2;
}

bigfloat log10(bigfloat const &number, bigfloat const &EPS) {
  if (number <= bigfloat(0UL)) {
    throw std::invalid_argument("logarithm of non-positive number");
  }

  bigfloat ln10 = log(bigfloat(10UL), EPS);

  return log(number, EPS) / ln10;
}
