/**
 * @file cs19_dollar_amount.cpp
 *
 * A class representing an amount in USD currency.
 *
 * @author Karen Corscadden, a student in CS 19 at Cabrillo College, kmcorscadden@jeff.cis.cabrillo.edu
 */

#include "cs19_dollar_amount.h"
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace cs19 {
DollarAmount::DollarAmount() {
  this->cents = 0;
}
DollarAmount::DollarAmount(double initial_amount) {
  this->cents = static_cast<int64_t>(std::llround(initial_amount * 100.0));
}
DollarAmount::DollarAmount(std::string initial_amount) {
  size_t i = 0;
  int64_t digits = 0;
  bool neg = false;
  if (initial_amount[i] == '-') {
    neg = true;
    i++;
  }
  if (initial_amount[i] != '$') {
    throw std::domain_error(std::string("Invalid sequence for DollarAmount. Missing $."));
  }
  i++;
  unsigned j = 0;
  std::string sdigits = initial_amount.substr(i);
  for (char c : sdigits) {
    if (!(std::isdigit(static_cast<unsigned char>(c)) || c == '.')) {
      throw std::domain_error(std::string("Invalid sequence for DollarAmount. Invalid characters in string."));
    }
    if (c == '.') {
      if (j == 0) {
        j++;
      } else if (j > 0) {
        throw std::domain_error(std::string("Invalid sequence for DollarAmount. Multiple decimals."));
      }
    } else {
      digits = digits * 10 + (c - '0');
      if (j > 0) {
        j++;
      }
    }
    if (j > 3) {
      throw std::domain_error(std::string("Invalid sequence for DollarAmount. Too many digits after decimal."));
    }
  }
  if (j != 3) {
    throw std::domain_error(std::string("Invalid sequence for DollarAmount. Not enough digits after decimal or no decimal."));
  }
  if (neg == true) {
    digits = -digits;
  }
  this->cents = digits;
}
DollarAmount::DollarAmount(const char* initial_amount) {
  size_t i = 0;
  int64_t digits = 0;
  bool neg = false;
  if (initial_amount[i] == '-') {
    neg = true;
    i++;
  }
  if (initial_amount[i] != '$') {
    throw std::domain_error(std::string("Invalid sequence for DollarAmount. Missing $."));
  }
  i++;
  unsigned j = 0;
  for (; initial_amount[i]; i++) {
    if (!(std::isdigit(static_cast<unsigned char>(initial_amount[i])) || initial_amount[i] == '.')) {
      throw std::domain_error(std::string("Invalid sequence for DollarAmount. Invalid characters in string."));
    }
    if (initial_amount[i] == '.') {
      if (j == 0) {
        j++;
      } else if (j > 0) {
        throw std::domain_error(std::string("Invalid sequence for DollarAmount. Multiple decimals."));
      }
    } else {
      digits = digits * 10 + (initial_amount[i] - '0');
      if (j > 0) {
        j++;
      }
    }
    if (j > 3) {
      throw std::domain_error(std::string("Invalid sequence for DollarAmount. Too many digits after decimal."));
    }
  }
  if (j != 3) {
    throw std::domain_error(std::string("Invalid sequence for DollarAmount. Not enough digits after decimal or no decimal."));
  }
  if (neg == true) {
    digits = -digits;
  }
  this->cents = digits;
}
int64_t DollarAmount::in_cents() const {
  return this->cents;
}
double DollarAmount::to_double() const {
  double dcents = static_cast<double>(this->cents) / 100.0;
  return dcents;
}
std::string DollarAmount::to_string() const {
  std::stringstream amount;
  amount << std::fixed << std::setprecision(2);
  if (this->cents < 0) {
    amount << "-$" << -this->to_double();
  } else {
    amount << '$' << this->to_double();
  }
  return amount.str();
}
std::vector<int> DollarAmount::to_denominations() const {
  int64_t numcents = this->cents;
  std::vector<int> amounts{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<int> dems{10000, 5000, 2000, 1000, 500, 100, 25, 10, 5, 1};
  unsigned i = 0;
  for (int dem : dems) {
    amounts[i] = numcents / dem;
    numcents = numcents - (amounts[i] * dem);
    ++i;
  }
  return amounts;
}
DollarAmount DollarAmount::operator+(const DollarAmount& that) const {
  DollarAmount ret;
  ret.cents = this->cents + that.cents;
  return ret;
}
DollarAmount DollarAmount::operator-(const DollarAmount& that) const {
  DollarAmount ret;
  ret.cents = this->cents - that.cents;
  return ret;
}
DollarAmount DollarAmount::operator*(const DollarAmount& that) const {
  DollarAmount ret;
  double temp = (double)this->cents * (double)that.cents;
  ret.cents = static_cast<int64_t>(std::llround(temp / 100.0));
  return ret;
}
DollarAmount DollarAmount::operator/(const DollarAmount& that) const {
  DollarAmount ret;
  double temp = (double)this->cents / (double)that.cents;
  ret.cents = static_cast<int64_t>(std::llround(temp * 100.0));
  return ret;
}
DollarAmount DollarAmount::operator%(const DollarAmount& that) const {
  DollarAmount ret;
  ret.cents = this->cents % that.cents;
  return ret;
}
DollarAmount& DollarAmount::operator+=(const DollarAmount& that) {
  this->cents += that.cents;
  return *this;
}
DollarAmount& DollarAmount::operator-=(const DollarAmount& that) {
  this->cents -= that.cents;
  return *this;
}
DollarAmount& DollarAmount::operator*=(const DollarAmount& that) {
  double temp = (double)this->cents * (double)that.cents;
  this->cents = static_cast<int64_t>(std::llround(temp / 100.0));
  return *this;
}
DollarAmount& DollarAmount::operator/=(const DollarAmount& that) {
  double temp = (double)this->cents / (double)that.cents;
  this->cents = static_cast<int64_t>(std::llround(temp * 100.0));
  return *this;
}
DollarAmount& DollarAmount::operator%=(const DollarAmount& that) {
  this->cents %= that.cents;
  return *this;
}
DollarAmount& DollarAmount::operator--() {
  this->cents -= 100;
  return *this;
}
DollarAmount DollarAmount::operator--(int) {
  DollarAmount ret = *this;
  this->cents -= 100;
  return ret;
}
DollarAmount& DollarAmount::operator++() {
  this->cents += 100;
  return *this;
}
DollarAmount DollarAmount::operator++(int) {
  DollarAmount ret = *this;
  this->cents += 100;
  return ret;
}
DollarAmount DollarAmount::operator-() const {
  DollarAmount ret;
  ret.cents = -this->cents;
  return ret;
}
// bool DollarAmount::operator<=>(const DollarAmount& that) const{
//   int8_t ret;
//   if (this->cents < that.cents) {
//     ret = -1;
//   } else if (this->cents > that.cents) {
//     ret = 1;
//   } else if (this->cents == that.cents) {
//     ret = 0;
//   }
//   return ret;
// }
std::istream& operator>>(std::istream& stream, DollarAmount& amount) {
  std::string digits;
  stream >> digits;
  amount = digits;
  return stream;
}
std::ostream& operator<<(std::ostream& stream, const DollarAmount& amount) {
  stream << amount.to_string();
  return stream;
}

}  // namespace cs19
