#include <cassert>
#include <numeric>
#include <iostream>
#include "cs19_range.h"

int main() {
  cs19::Range test_range(100, 1000, 3);
  // std::copy(test_range.begin(), test_range.end(), std::ostream_iterator<int>(std::cout, ", "));
  assert(std::accumulate(test_range.begin(), test_range.end(), 0) == 164550);
  cs19::Range test_range_2(1000, -1000, -3);
  // std::copy(test_range_2.begin(), test_range_2.end(), std::ostream_iterator<int>(std::cout, ", "));
  assert(std::accumulate(test_range_2.begin(), test_range_2.end(), 0) == 667);
  std::cout << "All asserts passed!" << std::endl;
}