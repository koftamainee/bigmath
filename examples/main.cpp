#include <iostream>
#include <chrono>
#include "bigmath.hpp"

using clock_t2 = std::chrono::steady_clock;
using ms       = std::chrono::milliseconds;
using us       = std::chrono::microseconds;

static auto now() { return clock_t2::now(); }
static long long elapsed_ms(clock_t2::time_point t) {
    return std::chrono::duration_cast<ms>(now() - t).count();
}
static long long elapsed_us(clock_t2::time_point t) {
    return std::chrono::duration_cast<us>(now() - t).count();
}

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
    std::cout << "=== bigmath benchmark ===\n\n";
    //
    // {
    //     auto t = now();
    //     bigint val = bigint(2UL).pow(16384);
    //     std::cout << "2^16384\n";
    //     std::cout << "  digits (base 10) : " << val.size_in_base(10) << "\n";
    //     std::cout << "  time             : " << elapsed_us(t) << " us\n\n";
    // }
    //
    // {
    //     auto t = now();
    //     bigint val = fibonacci(500000);
    //     std::cout << "fibonacci(500000)\n";
    //     std::cout << "  digits (base 10) : " << val.size_in_base(10) << "\n";
    //     std::cout << "  time             : " << elapsed_ms(t) << " ms\n\n";
    // }

    {
        // auto t = now();
        bigint val = factorial(100000);
        std::cout << "factorial(10000)\n";
        std::cout << "  digits (base 10) : " << val.size_in_base(10) << "\n";
        // std::cout << "  time             : " << elapsed_ms(t) << " ms\n\n";
    }

    // {
    //     std::cout << "division benchmarks\n";
    //
    //     struct Case {
    //         unsigned int dividend_bits;
    //         unsigned int divisor_bits;
    //         const char*  label;
    //     };
    //     const Case cases[] = {
    //         {   256,   128, " 256-bit /  128-bit"},
    //         {  1024,   512, "1024-bit /  512-bit"},
    //         {  4096,  2048, "4096-bit / 2048-bit"},
    //         { 16384,  8192, "16384-bit/ 8192-bit"},
    //         { 16384,     1, "16384-bit/   1-limb"},
    //     };
    //
    //     for (const auto& c : cases) {
    //         bigint dividend = bigint(2UL).pow(c.dividend_bits) - bigint(1UL);
    //         bigint divisor  = bigint(2UL).pow(c.divisor_bits)  - bigint(1UL);
    //
    //         const int REPS = 200;
    //
    //         auto bench = [&](const char* name, auto fn) {
    //             auto t = now();
    //             for (int i = 0; i < REPS; ++i) fn();
    //             std::cout << "  " << name << "  " << c.label
    //                       << "  : " << (elapsed_us(t) / REPS) << " us/op\n";
    //         };
    //
    //         bench("tdiv_q ", [&]{ (void)dividend.tdiv_q(divisor); });
    //         bench("tdiv_r ", [&]{ (void)dividend.tdiv_r(divisor); });
    //         bench("tdiv_qr", [&]{ (void)dividend.tdiv_qr(divisor); });
    //         bench("fdiv_q ", [&]{ (void)dividend.fdiv_q(divisor); });
    //         bench("mod    ", [&]{ (void)dividend.mod(divisor); });
    //         std::cout << "\n";
    //     }
    //
    // }


  bigfloat eps(bigint(1UL), bigint("100000000000000"));
  bigfloat pi = bigfloat::PI(eps);
  std::cout << cos(pi, eps).to_decimal(10) << std::endl;
  std::cout << sin(pi, eps).to_decimal(10) << std::endl;
  std::cout << tg(pi, eps).to_decimal(10) << std::endl;
  std::cout << arctg(pi, eps).to_decimal(10) << std::endl;
  // std::cout << arcsin(pi).to_decimal(10) << std::endl;

    std::cout << "=== done ===\n";
    return 0;
}