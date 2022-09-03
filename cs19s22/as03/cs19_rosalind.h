/**
 * @file cs19_rosalind.h
 *
 * Function templates to solve a few of the introductory Rosalind problems.
 *
 * @author A student in CS 19, someone@jeff.cis.cabrillo.edu
 */

// Header guard ensures that the contents of this file will only be added once to an executable
#ifndef CS19_ROSALIND_H_
#define CS19_ROSALIND_H_

#include <tuple>

namespace cs19 {
/**
 * Counts the occurrences of each nucleotide in a DNA string, similar to Rosalind problem DNA.
 * See: http://rosalind.info/problems/dna/
 *
 * @tparam DnaSequence an iterable type that supports iteration with a range-based loop, and
 * contains A/C/G/T char values, e.g. std::string and std::vector<char>.
 *
 * @param dna a DNA sequence (assumed to contain A/C/G/T characters)
 * @return a tuple containing the number of occurrences of 'A', 'C', 'G', 'T' in dna, respectively
 */
template <typename DnaSequence>
std::tuple<int, int, int, int> nucleotide_counts(const DnaSequence &dna) {
  int a_count = 0;
  int c_count = 0;
  int g_count = 0;
  int t_count = 0;
  for (char nuc : dna) {
    if (nuc == 'A') {
      ++a_count;
    } else if (nuc == 'C') {
      ++c_count;
    } else if (nuc == 'G') {
      ++g_count;
    } else if (nuc == 'T') {
      ++t_count;
    }
  }
  return std::make_tuple(a_count, c_count, g_count, t_count);
}

/**
 * Returns a RNA sequence transcribed from a DNA sequence, similar to Rosalind problem RNA.
 * See: http://rosalind.info/problems/rna/
 *
 * @tparam NucleotideSequence a random-access container type offering operations similar to
 * std::string and std::vector<char>, e.g. member function size(), indexing with indexes from 0 to
 * size() - 1, and copying via assignment.
 *
 * @param dna a DNA sequence (assumed to contain A/C/G/T characters)
 * @return an object of the same type representing the transcribed RNA version of the input DNA
 */
template <typename NucleotideSequence>
NucleotideSequence transcribe(const NucleotideSequence &dna) {
  auto rna = dna;
  for (std::size_t i = 0; i < rna.size(); ++i) {
    if (rna[i] == 'T') {
      rna[i] = 'U';
    }
  }
  return rna;
}

/**
 * Returns the reverse complement of a DNA sequence, similar to Rosalind problem RNA.
 * See: http://rosalind.info/problems/revc/
 *
 * @tparam DnaSequence a random-access container type offering operations similar to std::string and
 * std::vector<char>, e.g. member function size(), indexing with indexes from 0 to size() - 1, and
 * copying via assignment.
 *
 * @param dna a DNA sequence (assumed to contain A/C/G/T characters)
 * @return an object of the same type, representing reverse complement of the input DNA
 */
template <typename DnaSequence>
DnaSequence reverse_complement(const DnaSequence &dna) {
  auto revcomp = dna;
  std::size_t size = dna.size();
  for (std::size_t i = 0; i < size; ++i) {
    if (dna[size - 1 - i] == 'A') {
      revcomp[i] = 'T';
    } else if (dna[size - 1 - i] == 'T') {
      revcomp[i] = 'A';
    } else if (dna[size - 1 - i] == 'C') {
      revcomp[i] = 'G';
    } else if (dna[size - 1 - i] == 'G') {
      revcomp[i] = 'C';
    }
  }
  return revcomp;
}

/**
 * Returns the Hamming distance between two sequence, similar to Rosalind problem HAMM.
 * See: http://rosalind.info/problems/hamm/
 *
 * @tparam NucleotideSequence a random-access container type offering operations similar to
 * std::string and std::vector<char>, e.g. member function size(), and indexing with indexes from 0
 * to size() - 1.
 *
 * @param seq1 the first sequence
 * @param seq2 the second sequence
 * @return the Hamming distance between the two sequences, or -1 if they are of unequal length
 */
template <typename NucleotideSequence>
unsigned hamming_distance(const NucleotideSequence &seq1, const NucleotideSequence &seq2) {
  int ham = 0;
  if (seq1.size() != seq2.size()) {
    return -1;
  }
  for (std::size_t i = 0; i < seq1.size(); ++i) {
    if (seq1[i] != seq2[i]) {
      ++ham;
    }
  }
  return ham;
}

}  // namespace cs19

#endif  // CS19_ROSALIND_H