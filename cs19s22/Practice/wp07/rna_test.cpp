/**
 * @file rna_test.cpp
 *
 * Testing our preliminary object-oriented approach to some Rosalind problems.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */

#include <cassert>
#include <iostream>
#include <sstream>
#include "cs19_rna.h"

// We should experiment with RNA objects in cling, but this main has some basic tests as well.
// Make sure to specify C++17: cling -std=c++17
int main() {
  std::string test_string("GAUUACA");
  cs19::Rna rna(test_string);                              // Rna(const Sequence &)
  assert(rna.to_string() == test_string);                  // to_string()
  cs19::Rna other_rna{'G', 'A', 'U', 'U', 'A', 'C', 'A'};  // Rna(initializer_list<char>)
  assert(other_rna == test_string);                        // operator==(const Sequence &)
  for (int i = 0; i < rna.size(); ++i)                     // size()
    assert(rna[i] == test_string[i]);                      // operator[](std::size_t)
  auto complement = ~rna;                                  // operator~()
  assert(complement == "CUAAUGU");                         // operator==(const char *)
  auto reverse_complement = -complement;                   // operator-()
  assert(reverse_complement == "UGUAAUC");                 // operator==(const char *)
  assert(reverse_complement != rna);                       // operator==(const Rna&)
  auto duplicated = rna + rna;                             // operator+(const Rna&)
  assert(duplicated == test_string + test_string);         // operator==(const Sequence&)
  auto quadrupled = rna * 4;                               // operator*(std::size_t)
  auto test_string_quadrupled = test_string + test_string + test_string + test_string;
  assert(quadrupled == test_string_quadrupled);  // operator==(const Sequence&)
  double gc_c = rna.gc_content();                // gc_content()
  assert(gc_c == 2.0 / 7);
  assert(rna.count('A') == 3 && rna.count('C') == 1 && rna.count('G') == 1 && rna.count('U') == 2);
  auto counts = rna.nucleotide_counts();  // nucleotide_counts()
  assert(counts['A'] == 3 && counts['C'] == 1 && counts['G'] == 1 && counts['U'] == 2);
  // subsequence(std::size_t, std::size_t), size(), operator==(const Rna &)
  assert(quadrupled.subsequence(0, rna.size()) == rna);

  // Test constructor exception
  try {
    cs19::Rna bad_rna("UCSC");
    assert(false);  // We should't reach here. The line above should raise an error.
  } catch (const std::domain_error &error) {
    assert(true);  // All is well if we reach this catch clause
  }

  // Test stream insertion
  std::ostringstream buf;
  buf << rna;  // operator<<(std::ostream &, const Rna &)
  assert(buf.str() == test_string);

  // Test stream extraction: Assignment 01(ish)!
  cs19::Rna test;
  std::cin >> test;  // operator>>(std::istream &, Rna &)
  std::cout << test.gc_content() * 100 << '\n';

  // back(), pop_back() just like STL containers
  test_string = test.to_string();
  while (test) {
    assert(test.back() == test_string.back());
    test.pop_back();
    test_string.pop_back();
  }
}