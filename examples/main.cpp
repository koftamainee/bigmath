#include <iostream>
#include "bigmath.hpp"

static bigint factorial(unsigned long int n) {
  bigint result(1UL);
  for (unsigned long int i = 2; i <= n; ++i)
    result *= bigint(i);
  return result;
}

static bigint fibonacci(unsigned long int n) {
  if (n == 0) return bigint(0UL);
  if (n == 1) return bigint(1UL);
  bigint a(0UL), b(1UL);
  for (unsigned long int i = 2; i <= n; ++i) {
    bigint c = a + b;
    a = std::move(b);
    b = std::move(c);
  }
  return b;
}

int main() {
  constexpr unsigned long int FACT_N = 10000;
  constexpr unsigned long int FIB_N  = 100000;

  bigint fact = factorial(FACT_N);
  bigint fib  = fibonacci(FIB_N);

  std::cout << FACT_N << "! =\n" << fact << "\n\n";
  std::cout << "fib(" << FIB_N << ") =\n" << fib << "\n";
}