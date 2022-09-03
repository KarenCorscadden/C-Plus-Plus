#include <cassert>
#include <list>
#include <string>
#include "cs19_search_sort.h"

int main() {
  std::string data = "a1b2c3";
  cs19::bubble_sort(data);
  assert(data == "123abc");
  data = "Santa Cruz";
  cs19::selection_sort(data);
  assert(data == " CSaanrtuz");
  assert(cs19::linear_search(data, 'a') == 3);
  assert(cs19::binary_search(data, 'S') == 2);
  assert(cs19::binary_search(data, '!') == -1);

  std::list<int> more_data = {5, 4, 3, 2, 1};
  cs19::bubble_sort(more_data.begin(), more_data.end());
  assert(more_data == std::list<int>({1, 2, 3, 4, 5}));
  assert(cs19::linear_search(more_data.begin(), more_data.end(), 1) == more_data.begin());
  assert(cs19::linear_search(more_data.begin(), more_data.end(), 0) == more_data.end());
}