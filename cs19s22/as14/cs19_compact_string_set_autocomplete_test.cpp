/**
 * @file cs19_compact_string_set_autocomplete_test.cpp
 *
 * An interactive test of our specialized string set.
 *
 * @author Jeffrey Bergamini for CS 19, jbergamini@jeff.cis.cabrillo.edu
 */

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
#include "cs19_compact_string_set.h"

int main(int argc, char **argv) {
  // Populate a set with all word-like tokens in a file (e.g. /srv/datasets/joyce-ulysses.txt)
  std::ifstream input_file(argv[1]);
  cs19::CompactStringSet dictionary;
  std::for_each(std::istream_iterator<std::string>(input_file),
                std::istream_iterator<std::string>(), [&dictionary](auto word) {
                  std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                  word.erase(word.begin(), std::find_if(word.begin(), word.end(), ::isalpha));
                  word.erase(std::find_if(word.rbegin(), word.rend(), ::isalpha).base(),
                             word.end());
                  dictionary.insert(word);
                });
  std::cerr << "Set loaded with " << dictionary.size() << " strings.\n\n";
  // Query it! (e.g. under 50, rose 15, ab 100, n 500)
  std::string query;
  int num;
  for (std::cout << "> "; std::cin >> query >> num; std::cout << "> ") {
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);
    auto suggestions = dictionary.autocomplete(query, num);
    std::copy(suggestions.begin(), suggestions.end(),
              std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << '\n';
  }
}