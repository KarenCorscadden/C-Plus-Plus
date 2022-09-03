// Consist of at least a main function in a separate source-code file.
// You may also create other source-code/header files, if you wish.
// Read, from standard input, any number of whitespace-delimited integer tokens,
// assumed to fall within the range of int on our server.
// (You'll probably want to do something like place the integers into a std::vector<int>.)
// Use cs19::counting_sort to sort those integers.
// (If you've stored the integers in a std::vector, a handy way of calling cs19_counting_sort
// would be to pass the return value of std::vector::data() as the first argument,
// and the return value of std::vector::size() as the second argument.)
// Print, to standard output, the sorted integers, one per line.

#include <iostream>
#include <vector>
#include "cs19_counting_sort.h"

int main() {
  std::vector<int> tokens;
  for (int token; std::cin >> token;) {
    tokens.push_back(token);
  }
  cs19::counting_sort(tokens.data(), tokens.size());
  for (int token : tokens) {
    std::cout << token << std::endl;
  }
}