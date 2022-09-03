/**
 * @file cs19_dollar_amount.h
 *
 * A class representing an amount in USD currency.
 *
 * @author Karen Corscadden, a student in CS 19 at Cabrillo College, kmcorscadden@jeff.cis.cabrillo.edu
 */
#ifndef CS19_DOLLAR_AMOUNT_H_
#define CS19_DOLLAR_AMOUNT_H_

#include <compare>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace cs19 {

// Represents an amount in USD that supports various overloadedepsil

class DollarAmount {
 public:
  DollarAmount();                            // default constructor ($0.00)
  DollarAmount(double initial_amount);       // double constructor (amount in dollars)
  DollarAmount(std::string initial_amount);  // string constructor (format: "$D.CC")
  DollarAmount(const char* initial_amount);  // C-string constructor (format: "$D.CC")
  int64_t in_cents() const;                  // returns this amount in cents
  double to_double() const;                  // returns this amount to double precision
  std::string to_string() const;             // format: "$D.CC"
  // returns a vector describing the minimum number of denominations required to represent this
  // amount, respectively in bills ($100, $50, $20, $10, $5, $1) and coins ($.25, $.10, $.05, $.01)
  std::vector<int> to_denominations() const;
  // Binary arithmetic operators
  DollarAmount operator+(const DollarAmount& that) const;
  DollarAmount operator-(const DollarAmount& that) const;
  DollarAmount operator*(const DollarAmount& that) const;
  DollarAmount operator/(const DollarAmount& that) const;
  DollarAmount operator%(const DollarAmount& that) const;
  // Compound assignment operators
  DollarAmount& operator+=(const DollarAmount& that);
  DollarAmount& operator-=(const DollarAmount& that);
  DollarAmount& operator*=(const DollarAmount& that);
  DollarAmount& operator/=(const DollarAmount& that);
  DollarAmount& operator%=(const DollarAmount& that);
  // Increment and decrement operators (increase/reduce an object by $1.00)
  DollarAmount& operator--();    // prefix decrement
  DollarAmount operator--(int);  // postfix decrement (must return a copy of the pre-mutated object)
  DollarAmount& operator++();    // prefix increment
  DollarAmount operator++(int);  // postfix increment (must return a copy of the pre-mutated object)
  // Unary minus operator
  DollarAmount operator-() const;
  // Three-way comparison should probably work by default:
  // https://en.cppreference.com/w/cpp/language/default_comparisons
  // If not, you need to get your comparisons working regardless:
  // <, <=, ==, !=, >, >=
  auto operator<=>(const DollarAmount& that) const = default;
  // Stream insertion and extraction (format: "$D.CC").
  // Remember that these are not actually member functions, but rather global functions.
  friend std::istream& operator>>(std::istream& stream, DollarAmount& amount);
  friend std::ostream& operator<<(std::ostream& stream, const DollarAmount& amount);

 private:
  // TODO (decide on appropriate member variable(s))
  int64_t cents;
};

}  // namespace cs19

#endif