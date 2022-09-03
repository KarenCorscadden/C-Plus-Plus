#include <vector>
#include <iostream>

template <typename IterableNumbers>
double arithmetic_mean(const IterableNumbers *values) {
  double sum = 0;
  // Range-based for loop: Accesses all values in an iterable object (e.g. std::vector, std::string)
  for (auto value : *values)
    sum += value;
  return sum / values->size();
}

int main() {
  std::vector<int> nums{1, 2, 3, 4, 5};
  std::cout << arithmetic_mean(&nums) << std::endl;
}