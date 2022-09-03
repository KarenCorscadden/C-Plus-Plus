/**
 * @file set_spell_checker.cpp
 *
 * Quick and dirty spell checker, printing misspelled words one per line to stdout.
 *
 * @author Jeffrey Bergamini for CS 19, jbergamini@jeff.cis.cabrillo.edu
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_set>
#include "cs19_compact_string_set.h"

int main(int argc, char** argv) {
  // file for spell-checking dictionary
  std::ifstream dict_file(argc > 1 ? argv[1] : "/usr/share/dict/american-english-insane");

  // std::set<std::string> dictionary;  // choose this data structure...
  // std::unordered_set<std::string> dictionary;  // or this one...
  cs19::CompactStringSet dictionary;  // ...or this one
  for (std::string word; std::getline(dict_file, word);) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    dictionary.insert(word);
  }

  // Copy "words" (whitespace-delimited tokens, trimmed of non-English letters) to stdout, one word
  // per line, if not found in the dictionary (case-insensitive).
  std::copy_if(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(),
               std::ostream_iterator<std::string>(std::cout, "\n"), [&dictionary](auto word) {
                 std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                 word.erase(word.begin(), std::find_if(word.begin(), word.end(), ::isalpha));
                 word.erase(std::find_if(word.rbegin(), word.rend(), ::isalpha).base(), word.end());
                 return word.length() > 0 && dictionary.find(word) == dictionary.end();
               });
}