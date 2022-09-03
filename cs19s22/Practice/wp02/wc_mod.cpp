/**
 * @file wc_mod.cpp
 *
 * Approximates some of the wc utility (counting lines, words, and bytes), e.g.:
 * // input: files as command line arguments; stdout: terminal
 * ./wc <path to file>
 *
 * @author Karen Corscadden for CS 19, kmcorscadden@jeff.cis.cabrillo.edu
 * Modified from wc.cpp authored by Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */

#include <iostream>  // std::(cin|cout)
#include <sstream>   // std::istringstream
#include <string>    // std::getline
#include <fstream>   // std:ifstream

/**
 * Uses a stringstream to count the number of whitespace-delimited "words" in a string.
 *
 * @param line the string to analyze
 * @return the number of whitespace-delimited "words" in line
 */
int count_words(const std::string &line) {
  // const: this function is not allowed to change the state of object "line"
  // &line: string object will be passed "by reference", i.e. the original object instead of a copy
  int word_count = 0;
  std::istringstream line_stream(line);  // Lets us treat a string like an input/output stream
  // Extraction operator evaluates to true if input stream not in a fail/EOF state
  for (std::string token; line_stream >> token;)
    ++word_count;
  return word_count;
}

// Modified to expect file paths as command line arguments
int main(int argc, char **argv) {
  // argc: argument count (including this program)
  // argv: actual command-line arguments (as an array of C strings: char *)
  // argv[0]: this executable
  // argv[1]: first command-line arg

  int num_lines = 0;
  int num_words = 0;
  int num_bytes = 0;

  for (int i = 1; i < argc; ++i) {
    std::ifstream in_file(argv[i]); // assume argv[i] is a path to a readable file

    // This std::getline call returns std::cin; input streams are "true" if not in a fail/EOF state
    for (std::string line; std::getline(in_file, line);) {
      ++num_lines;
      num_words += count_words(line);
      num_bytes += line.size() + 1;  // Newline character is one extra input byte for each line
    }
  }
  std::cout << num_lines << ' ' << num_words << ' ' << num_bytes << '\n';
}