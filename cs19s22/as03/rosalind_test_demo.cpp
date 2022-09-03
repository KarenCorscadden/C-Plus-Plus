/**
 * @file rosalind_test_demo.cpp
 *
 * Assertion-based tests for functions in cs19_rosalind.h.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */

#include <cassert>
#include <string>
#include <tuple>
#include <vector>

#include "cs19_rosalind.h"

int main() {
  std::string gattaca_string = "GATTACA";
  std::vector<char> gattaca_vector = {'G', 'A', 'T', 'T', 'A', 'C', 'A'};

  auto expected_counts = std::make_tuple(3, 1, 1, 2);
  assert(cs19::nucleotide_counts(gattaca_string) == expected_counts);
  assert(cs19::nucleotide_counts(gattaca_vector) == expected_counts);

  std::string expected_rna_string = "GAUUACA";
  std::vector<char> expected_rna_vector = {'G', 'A', 'U', 'U', 'A', 'C', 'A'};
  assert(cs19::transcribe(gattaca_string) == expected_rna_string);
  assert(cs19::transcribe(gattaca_vector) == expected_rna_vector);

  std::string expected_revc_string = "TGTAATC";
  std::vector<char> expected_revc_vector = {'T', 'G', 'T', 'A', 'A', 'T', 'C'};
  assert(cs19::reverse_complement(gattaca_string) == expected_revc_string);
  assert(cs19::reverse_complement(gattaca_vector) == expected_revc_vector);

  assert(cs19::hamming_distance(std::string("GAGCCTACTAACGGGAT"),
                                std::string("CATCGTAATGACGGCCT")) == 7);
  assert(cs19::hamming_distance(gattaca_vector, expected_rna_vector) == 2);
  assert(cs19::hamming_distance(std::string("GATTACA"), std::string("GAT")) == -1);
}