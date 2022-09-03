/**
 * @file vector_binary_search_spell_checker.cpp
 *
 * Quick and dirty spell checker, printing misspelled words one per line to stdout.
 * std::binary_search() exists!
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  std::vector<std::string> dictionary;  // choose this data structure...
  {
    // file for spell-checking dictionary
    std::ifstream dict_file(argc > 1 ? argv[1] : "/usr/share/dict/american-english-insane");
    for (std::string word; std::getline(dict_file, word);) {
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      dictionary.push_back(word);
    }
    // Must take the time to pre-sort data if using binary search (unless dictionary comes sorted)
    std::sort(dictionary.begin(), dictionary.end());
  }

  // Copy "words" (whitespace-delimited tokens, trimmed of non-English letters) to stdout, one word
  // per line, if not found in the dictionary (case-insensitive).
  std::copy_if(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(),
               std::ostream_iterator<std::string>(std::cout, "\n"), [&dictionary](auto word) {
                 std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                 word.erase(word.begin(), std::find_if(word.begin(), word.end(), ::isalpha));
                 word.erase(std::find_if(word.rbegin(), word.rend(), ::isalpha).base(), word.end());
                 return word.length() > 0 &&
                        !std::binary_search(dictionary.begin(), dictionary.end(), word);
               });
}