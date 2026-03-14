#include <cstring>
#include <exception>

#include "bigmath/bigfloat.hpp"

std::ostream &operator<<(std::ostream &out, bigfloat const &num) noexcept {
  if (num == bigfloat(0UL)) {
    out << 0;
    return out;
  }
  if (num.denominator_ < 0L) {
    out << "-";
  }
  if (num.denominator_ != 1L) {
    out << num.numerator_ << "/" << num.denominator_.abs();
  } else {
    out << num.numerator_;
  }
  return out;
}

std::string bigfloat::to_decimal(size_t precision) const {
  const bool is_negative = (denominator_ < 0L);

  bigint abs_num = numerator_.abs();
  bigint abs_den = denominator_.abs();

  auto [integer_part, remainder] = abs_num.tdiv_qr(abs_den);

  std::string result;

  if (is_negative) {
    result += "-";
  }

  result += integer_part.to_string();

  if (remainder != 0UL && precision > 0) {
    result += ".";

    for (size_t i = 0; i < precision; ++i) {
      remainder *= 10;
      bigint digit = remainder / abs_den;
      remainder %= abs_den;

      result += digit.to_string();

      if (remainder == 0UL) {
        break;
      }
    }
  }

  return result;
}
