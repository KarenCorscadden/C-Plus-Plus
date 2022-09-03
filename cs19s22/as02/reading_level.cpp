// @author Karen Corscadden for CS19 kmcorscadden@jeff.cis.cabrillo.edu

// 1. Read in a body of text on standard input. Can be multiple lines.
// 2. Calculates a modified version of the automated readability index.
// 3. Prints the estimated grade level of the text on standard output accurate to 3 places.

#include <iostream>
#include <string>
#include <cctype>

int main() {
  int c_count = 0;
  int w_count = 0;
  int s_count = 0;
  float reading_lvl = 0;

  for (std::string token; std::cin >> token;) {
    bool is_word = false;
    bool is_sentence = false;
    // iterate through characters in string
    for (unsigned char character : token) {
      if (std::isalpha(character)) {
        ++c_count;
        is_word = true;
      } else if (is_word == true && (character == '.' || character == '!' || character == '?')) {
        is_sentence = true;
      }
    }
    if (is_word == true) {
        ++w_count;
      }
    if (is_sentence == true) {
        ++s_count;
    }
  }
  // calculate reading level
  // empty input : -nan is ok
  // single isalpha character: inf is ok

  reading_lvl = (4.71 * c_count / w_count) + (0.5 * w_count / s_count) - 21.43;

  std::cout << std::fixed;
  std::cout.precision(3);
  std::cout << reading_lvl << "\n";
}