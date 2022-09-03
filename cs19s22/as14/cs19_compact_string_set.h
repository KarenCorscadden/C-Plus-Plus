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
#include <vector>

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
    std::shared_ptr<Node> sibling = nullptr;
    std::shared_ptr<Node> child = nullptr;
  };

 public:
  /** Inserts a string into this set, if not already present. */
  bool insert(const std::string& value);
  /** Returns whether this set contains a given string. */
  bool find(const std::string& value) const;
  /**
   * Removes a string from this set, if present. Deleting subsequently unused nodes is optional.
   *
   * @param value the string to remove
   * @return whether the string had been present in the set
   */
  bool erase(const std::string& value);
  /** For matching find() with end(), a la std::set */
  bool end() const {
    return false;
  }
  /** Returns the number of strings in this set. */
  std::size_t size() const {
    return this->num_strings_;
  }
  /**
   * Returns the closest n strings to the given string, in "autocomplete" fashion. Proximity shall
   * be measured as follows: A child node is the closest to a given node, and any of its siblings
   * are the next closest, in order of their sibling links.
   *
   * @param base the string from which to suggest autocompletions
   * @param n the maximum number of autocompletions to return
   * @return at most n autocompletions of the base, in descending order of proximity from the base
   */
  std::vector<std::string> autocomplete(const std::string& base, std::size_t n) const;

 private:
  Node root_{};                 // A dummy node for the starting point of the set
  std::shared_ptr<Node> root_ptr = std::make_shared<Node> (root_);
  std::size_t num_strings_ = 0;  // The number of strings in the set
  Node * find_next(const Node *base, char to_find) const;
};

}  // namespace cs19

#endif