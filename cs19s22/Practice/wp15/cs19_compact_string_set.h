/**
 * @file cs19_compact_string_set.h
 *
 * A first-draft interface of our specialized string set. No destructor yet.
 *
 * @author Jeffrey Bergamini for CS 19, jbergamini@jeff.cis.cabrillo.edu
 */
#ifndef CS19_COMPACT_STRING_SET_H_
#define CS19_COMPACT_STRING_SET_H_

#include <string>
#include <memory>

namespace cs19 {

/**
 * Class CompactStringSet represents a set of strings in a structure that is potentially more space-
 * and time-efficient than std::set<std::string>.
 */
class CompactStringSet {
  // Our internal element type (see diagrams from lecture)
  struct Node {
    Node() = default;  // default constructor
    char letter;              // each node stores a letter
    bool terminal = false;    // ... and is potentially the end of a string in the set
    std::shared_ptr<Node> sibling = nullptr;  // ... and may have "sibling" node(s) that also follow previous letter
    std::shared_ptr<Node> child = nullptr;    // ... and may have a "child" node for the next letter in a string
  };

 public:
  /** Inserts a string into this set, if not already present. */
  void insert(const std::string& value);
  /** Returns whether this set contains a given string. */
  bool find(const std::string& value) const;
  /** For matching find() with end(), a la std::set */
  bool end() const {
    return false;
  }
  /** Returns the number of strings in this set. */
  std::size_t size() const {
    return this->num_strings_;
  }

 private:
  Node root_{0};                 // A dummy node for the starting point of the set
  std::shared_ptr<Node> root_ptr = std::make_shared<Node> (root_);
  std::size_t num_strings_ = 0;  // The number of strings in the set
  std::weak_ptr<Node> find_next(const std::weak_ptr<Node> base, char to_find) const;  // Returns matching child or sibling node
};

}  // namespace cs19

#endif