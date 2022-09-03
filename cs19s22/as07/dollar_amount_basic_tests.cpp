/**
 * @file dollar_amount_basic_tests.cpp
 *
 * Testing class cs19::DollarAmount.
 *
 * @author Karen Corscadden, a student in CS 19 at Cabrillo College, kmcorscadden@jeff.cis.cabrillo.edu
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include "cs19_dollar_amount.h"

int main() {
  cs19::DollarAmount test;  // default constructor
  std::vector<int> expected_denoms = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::stringstream test_stream;
  
  assert(test.to_double() == 0.0);
  assert(test.in_cents() == 0);
  assert(test.to_string() == "$0.00");
  assert(test.to_denominations() == expected_denoms);
  test_stream << test;  // operator<<
  assert(test_stream.str() == "$0.00");
  test_stream.str("");

  test += {10};  // operator+= and direct initialization (implicit call to DollarAmount(10))
  assert(std::abs(test.to_double() - 10) <= .01);
  assert(test.in_cents() == 1000);
  assert(test.to_string() == "$10.00");
  expected_denoms = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
  assert(test.to_denominations() == expected_denoms);
  test_stream << test;
  assert(test_stream.str() == "$10.00");
  test_stream.str("");

  test -= {23.45};
  cs19::DollarAmount expected = {-13.45};  // implicit copy constructor
  cs19::DollarAmount epsilon(.01);         // DollarAmount(double)
  assert(test - expected <= epsilon);      // operator-, operator<=
  assert(test.in_cents() == -1345);
  assert(test.to_string() == "-$13.45");
  expected_denoms = {0, 0, 0, -1, -0, -3, -1, -2, 0, 0};
  assert(test.to_denominations() == expected_denoms);
  test_stream << test;
  assert(test_stream.str() == "-$13.45");
  test_stream.str("");

  test_stream << "$99.99";
  test_stream >> test;                             // operator>>
  assert(test-- == cs19::DollarAmount("$99.99"));  // operator--(int), operator==
  assert(std::abs(test.to_double() - 98.99) <= .01);
  assert(--test == cs19::DollarAmount("$97.99"));  // operator--(), operator==
  assert(test.in_cents() == 9799);
  assert(test.to_string() == "$97.99");
  expected_denoms = {0, 1, 2, 0, 1, 2, 3, 2, 0, 4};
  assert(test.to_denominations() == expected_denoms);
  test_stream.str("");
  std::cout << test << std::endl;
  std::cout << cs19::DollarAmount(2) << std::endl;
  std::cout << test + cs19::DollarAmount(2) << std::endl;
  std::cout << cs19::DollarAmount(99.99) << std::endl;
  std::cout << (test + cs19::DollarAmount(2) == cs19::DollarAmount(99.99)) << std::endl;
  assert(test + cs19::DollarAmount(2) == cs19::DollarAmount(99.99));
  std::string stest = "-$2700000000000000.00";
  cs19::DollarAmount test2(stest);
  std::cout << test2 << std::endl;
  assert(test2 == cs19::DollarAmount(-2700000000000000));
  stest = "27";
  try {
    cs19::DollarAmount test3(stest);
    assert(false);
  } catch (const std::domain_error &error) {
    assert(true);
  }
  stest = "$27.999";
  try {
    cs19::DollarAmount test4(stest);
    assert(false);
  } catch (const std::domain_error &error) {
    assert(true);
  } 
  try {
    cs19::DollarAmount test5("27");
    assert(false);
  } catch (const std::domain_error &error) {
    assert(true);
  }
  try {
    cs19::DollarAmount test6("27.999");
    assert(false);
  } catch (const std::domain_error &error) {
    assert(true);
  }
  try {
    cs19::DollarAmount test7("");
    assert(false);
  } catch (const std::domain_error &error) {
    assert(true);
  }
  stest = "";
  try {
    cs19::DollarAmount test8(stest);
    assert(false);
  } catch (const std::domain_error &error) {
    assert(true);
  }
  cs19::DollarAmount test9(50);
  test9 /= cs19::DollarAmount(2);
  assert(test9 == cs19::DollarAmount(25));
  test9 *= cs19::DollarAmount(2);
  std::cout << test9 << std::endl;
  assert(test9 == cs19::DollarAmount(50));
  assert(cs19::DollarAmount(25) == cs19::DollarAmount(50) / cs19::DollarAmount(2));
  assert(cs19::DollarAmount(50) == cs19::DollarAmount(25) * cs19::DollarAmount(2));
  assert(test9 % cs19::DollarAmount(25) == cs19::DollarAmount());
  test9 %= cs19::DollarAmount(49);
  std::cout << test9 << std::endl;
  assert(test9 == cs19::DollarAmount(1));
  cs19::DollarAmount test10(0.0);
  assert(cs19::DollarAmount(25) / cs19::DollarAmount(2.5) == cs19::DollarAmount(10));
  assert(cs19::DollarAmount(1) * cs19::DollarAmount(100) == cs19::DollarAmount(100));
  assert(cs19::DollarAmount(5) % cs19::DollarAmount(2) == cs19::DollarAmount(1));
  assert(cs19::DollarAmount(25) / cs19::DollarAmount(.5) == cs19::DollarAmount(50));

  cs19::DollarAmount test11(10);
  assert(test11 < cs19::DollarAmount(11));
  assert(test11 <= cs19::DollarAmount(11));
  assert(test11 <= cs19::DollarAmount(10));
  assert(test11 == cs19::DollarAmount(10));
  assert(test11 >= cs19::DollarAmount(9));
  assert(test11 > cs19::DollarAmount(9));
  assert(test11 != cs19::DollarAmount(9));
  assert(test11 != cs19::DollarAmount(11));
  assert(test11 != cs19::DollarAmount(10.01));
  assert(test11 != cs19::DollarAmount(9.99));

  cs19::DollarAmount test12 = test11;
  assert(test12 == test11);

  assert(cs19::DollarAmount(9.999) == cs19::DollarAmount("$10.00"));

  test9 %= cs19::DollarAmount(.3);
  std::cout << test9 << std::endl;
  assert(test9 == cs19::DollarAmount(.1));
  assert(cs19::DollarAmount(1) % cs19::DollarAmount(.3) == test9);
  assert(test11 * cs19::DollarAmount(-1) == cs19::DollarAmount(-10));
  assert(test11 * cs19::DollarAmount(-.25) == cs19::DollarAmount(-2.5));
  std::cout << cs19::DollarAmount(.5) * cs19::DollarAmount(.25) << std::endl;
  assert(cs19::DollarAmount(.5) * cs19::DollarAmount(.25) == cs19::DollarAmount(.125));
  std::cout << cs19::DollarAmount(1) / cs19::DollarAmount(150) << std::endl;
  assert(cs19::DollarAmount(1) / cs19::DollarAmount(150) == cs19::DollarAmount(.01));

  {
    cs19::DollarAmount a(-10.5);
    cs19::DollarAmount b(-.125);

    cs19::DollarAmount c = a;
    c *= b;
    std::cout << c << std::endl;
    assert(c == a * b);

    c = a;
    c /= b;
    std::cout << c << std::endl;
    assert(c == a / b);

    c = a;
    c %= b;
    std::cout << c << std::endl;
    assert(c == a % b);
  }
}