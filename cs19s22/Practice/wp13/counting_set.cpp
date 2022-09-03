/**
 * @file counting_set.cpp
 *
 * @author Karen Corscadden for CS 19, kmcorscadden@jeff.cis.cabrillo.edu
 */

#include <cassert>
#include <set>

namespace cs19 {

template <typename T>
struct NES_compare {
    bool operator()(const std::pair<T, int> &lhs, const std::pair<T, int> &rhs) const
    {
        return (lhs.first) < (rhs.first);
    }
};

template <typename T>
class Non_exclusive_set : public std::set<std::pair<T, int>, NES_compare<T> > {
  using super = std::set<std::pair<T, int>, NES_compare<T> >;
public:
  void insert(T val) {
    std::pair<T, int> to_insert{val, 1};
    auto it = this->find(to_insert);
    if (it != this->end()) {
      int current_count = it->second;
      to_insert.second += current_count;
      this->erase(it);
    }
    super::insert(to_insert);
  }
  int count(T key) {
    std::pair<T, int> key_pair{key, 0};
    auto it = this->find(key_pair);
    if (it != this->end()) {
      return it->second;
    } else {
      return 0;
    }
  }
};
}  // namespace cs19

int main() {
  cs19::Non_exclusive_set<int> x;
  x.insert(2);
  x.insert(2);
  assert(x.count(2) == 2);
}