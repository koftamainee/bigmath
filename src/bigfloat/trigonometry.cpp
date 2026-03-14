#include <cstdio>
#include <future>
#include <numeric>

#include "bigmath/bigfloat.hpp"

bigfloat bigfloat::PI(const bigfloat &EPS) {
  if (pi_cache_.find(EPS) != pi_cache_.cend()) {
    return bigfloat(pi_cache_[EPS]);
  }
  static const bigfloat one_fifth(bigint(1UL), bigint(5UL));
  static const bigfloat one_239(bigint(1UL), bigint(239UL));

  auto future_arctg_1_5 = std::async(std::launch::async, [&]() { return arctg(one_fifth, EPS / bigfloat(16UL)); });
  auto future_arctg_1_239 = std::async(std::launch::async, [&]() { return arctg(one_239, EPS / bigfloat(4UL)); });
  const bigfloat arctg_1_5(future_arctg_1_5.get());
  const bigfloat arctg_1_239(future_arctg_1_239.get());

  bigfloat pi = bigfloat(16UL) * arctg_1_5 - bigfloat(4UL) * arctg_1_239;
  pi_cache_[EPS] = pi;
  return bigfloat(pi);
}

bigfloat bigfloat::reduce_argument(const bigfloat &number, const bigfloat &EPS) {
  constexpr size_t reducing_threshold = 7;
  bigfloat reduced_x(number);

  if (reduced_x > bigfloat(reducing_threshold)) {
    bigfloat const two_pi = bigfloat::PI(EPS * bigfloat(2UL)) * bigfloat(2UL);
    bigfloat k = (number / two_pi).truncate();
    reduced_x = number - (k * two_pi);

    if (reduced_x > two_pi) {
      reduced_x -= two_pi;
    } else if (reduced_x < -two_pi) {
      reduced_x += two_pi;
    }
  }

  return bigfloat(reduced_x);
}

bigfloat sin(bigfloat const &number, bigfloat const &EPS) {
  bigfloat reduced_x = bigfloat::reduce_argument(number, EPS);
  bigfloat res(0UL);
  bigfloat term(reduced_x);
  bigfloat x_squared = reduced_x * reduced_x;
  bigint n(1UL);

  while (term.abs() > EPS) {
    res += term;
    term *= -x_squared;
    ++n;
    term /= bigfloat((bigint(2UL) * n - 1)) * bigfloat((bigint(2UL) * n - 2));
  }

  return bigfloat(res);
}

bigfloat cos(bigfloat const &number, bigfloat const &EPS) {
  bigfloat reduced_x = bigfloat::reduce_argument(number, EPS);
  bigfloat res(0UL);
  bigfloat term(1UL);
  bigfloat number_squared = reduced_x * reduced_x;
  bigint n(0UL);

  while (term.abs() > EPS) {
    res += term;
    term *= -number_squared;
    ++n;
    term /= bigfloat((bigint(2UL) * n - 1)) * bigfloat((bigint(2UL) * n));
  }

  return bigfloat(res);
}

bigfloat tg(const bigfloat &number, const bigfloat &EPS) {
  bigfloat pi = bigfloat::PI(EPS);
  bigfloat two(2UL);
  bigfloat half_pi = pi / two;
  bigfloat x(number);
  bool negate = false;

  if (x.abs() > pi) {
    x = x - (x / pi).truncate() * pi;
  }

  if (x > half_pi) {
    x = pi - x;
    negate = true;
    x.simplify();
  } else if (x <= -half_pi) {
    x = pi + x;
    negate = true;
    x.simplify();
  }
  if (x < bigfloat(0UL)) {
    x = -x;
    negate = !negate;
    x.simplify();
  }

  if (x.abs() > half_pi - EPS) {
    throw std::invalid_argument("tg: argument too close to pi/2");
  }

  bigfloat result(0UL);
  bigfloat term;
  bigfloat x_squared = x * x;
  bigfloat x_power(x);

  bigfloat pow_neg4_n = bigfloat(-4L);
  bigfloat pow_4_n = bigfloat(4L);

  bigfloat factorial(1UL);
  size_t n = 1;

  for (; n <= 1000; ++n) {
    const bigfloat &B = bigfloat::bernoulli_number(2 * n);
    bigfloat coef = B * pow_neg4_n * (bigfloat(1UL) - pow_4_n);

    factorial *= bigfloat((bigint(2) * n - 1) * (bigint(2) * n));

    term = coef * x_power / factorial;

    if (term.abs() < EPS) {
      break;
    }

    result += term;

    x_power *= x_squared;
    pow_neg4_n *= bigfloat(-4L);
    pow_4_n *= bigfloat(4L);
  }

  result.simplify();
  return negate ? -result : bigfloat(result);
}

bigfloat ctg(bigfloat const &number, bigfloat const &EPS) { return tg(number, EPS).reciprocal(); }

bigfloat sec(bigfloat const &number, bigfloat const &EPS) { return sin(number, EPS).reciprocal(); }

bigfloat cosec(bigfloat const &number, bigfloat const &EPS) { return cos(number, EPS).reciprocal(); }

bigfloat arcsin(const bigfloat &number, const bigfloat &EPS) {
  if (number.abs() > bigfloat(1UL)) {
    throw std::domain_error("arcsin is undefined for |x| > 1");
  }

  if (number.abs() > bigfloat(bigint(8UL), bigint(10UL))) {
    const bigfloat half_pi = bigfloat::PI(EPS) / bigfloat(2L);
    bigfloat sign = (number > bigfloat(0UL)) ? bigfloat(1L) : bigfloat(-1L);
    return sign * (half_pi - sqrt(arcsin((bigfloat(1UL) - number * number), EPS), EPS));
  }

  bigfloat term(number);
  bigfloat result(term);
  bigfloat number_squared = number * number;
  bigint n(1UL);

  do {
    term *= number_squared * bigfloat((bigint(2L) * n - bigint(1L)) * (bigint(2L) * n - bigint(1L)) / (bigint(2L) * n) *
                                      (bigint(2L) * n + bigint(1)));
    result += term;
    ++n;
  } while (term.abs() >= EPS);

  return bigfloat(result);
}

bigfloat arccos(bigfloat const &number, bigfloat const &EPS) {
  if (number.abs() > bigfloat(1UL)) {
    throw std::domain_error("arccos is undefined for |x| > 1");
  }

  return bigfloat::PI() / bigfloat(2UL) - arcsin(number, EPS);
}

bigfloat arcctg(bigfloat const &number, bigfloat const &EPS) {
  if (number.abs() <= bigfloat(1UL)) {
    return arctg(number.reciprocal(), EPS);
  }

  bigfloat reduced_x = bigfloat::reduce_argument(number, EPS);

  bigfloat term = reduced_x.reciprocal();
  bigfloat result(term);
  bigfloat x_squared_inv = term * term;
  bigint n(1UL);
  long sign = -1;

  do {
    term *= x_squared_inv;
    result += bigfloat(sign) * term / bigfloat((bigint(2UL) * n + bigint(1UL)));
    sign = -sign;
    n++;
  } while (term.abs() >= EPS);

  return bigfloat(result);
}

bigfloat arctg(bigfloat const &number, bigfloat const &EPS) {
  bigfloat reduced_x = bigfloat::reduce_argument(number, EPS);
  if (reduced_x.abs() > bigfloat(1UL)) {
    const bigfloat half_pi = bigfloat::PI(EPS) / bigfloat(2UL);
    return (reduced_x > bigfloat(0UL)) ? half_pi - arctg(reduced_x.reciprocal(), EPS)
                                       : -half_pi - arctg(reduced_x.reciprocal(), EPS);
  }
  if (reduced_x == bigfloat(1UL)) {
    return bigfloat::PI(EPS) / bigfloat(4UL);
  }

  bigfloat term(reduced_x);
  bigfloat result(term);
  bigfloat number_squared = reduced_x * reduced_x;
  bigint n(1UL);
  long sign = -1;

  do {
    term *= number_squared;
    result += (term * bigfloat(sign)) / bigfloat(n * 2UL + 1UL);
    sign = -sign;
    ++n;
  } while (term.abs() >= EPS);

  return bigfloat(result);
}

bigfloat arcsec(bigfloat const &number, bigfloat const &EPS) { return arccos(number.reciprocal(), EPS); }

bigfloat arccosec(bigfloat const &number, bigfloat const &EPS) { return arcsin(number.reciprocal(), EPS); }

const bigfloat &bigfloat::bernoulli_number(size_t n) {
  if (n >= bernoulli_cache_.size()) {
    compute_bernoulli_up_to(n);
  }
  return bernoulli_cache_[n];
}

void bigfloat::compute_bernoulli_up_to(size_t n) {
  while (bernoulli_cache_.size() <= n) {
    size_t m = bernoulli_cache_.size();

    if (m % 2 == 1 && m > 1) {
      bernoulli_cache_.emplace_back(0UL);
      continue;
    }

    bigfloat sum(0UL);
    for (size_t k = 0; k < m; ++k) {
      bigfloat coef = binomial(m + 1, k);
      sum += coef * bernoulli_cache_[k];
    }

    bigfloat Bm = -sum / bigfloat(static_cast<long>(m) + 1);
    bernoulli_cache_.push_back(Bm);
  }
}

bigfloat bigfloat::binomial(size_t n, size_t k) {
  if (k == 0 || k == n) {
    return bigfloat(1UL);
  }
  if (k > n) {
    return bigfloat(0UL);
  }

  bigfloat res(1UL);
  for (size_t i = 1; i <= k; ++i) {
    res *= bigfloat(static_cast<long>(n - k + i));
    res /= bigfloat(static_cast<long>(i));
  }
  return bigfloat(res);
}
