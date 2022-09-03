/**
 * @file cs19_compact_string_set.cpp
 *
 * A first-draft implementation of our specialized string set.
 *
 * @author Jeffrey Bergamini for CS 19, jbergamini@jeff.cis.cabrillo.edu
 */
#include "cs19_compact_string_set.h"
#include <string>
#include <memory>

namespace cs19 {

void CompactStringSet::insert(const std::string& value) {
  std::weak_ptr<CompactStringSet::Node> cur = this->root_ptr;                          // Start at the dummy "root" node.
  for (auto character : value) {                     // For each character...
    std::weak_ptr<CompactStringSet::Node> search = this->find_next(cur, character);  // ... find a child containing the character.
    if (search.lock()) {                                    // If such a node exists...
      cur = search;                                  // ... nothing to do. We just move on.
    } else {                                         // ... otherwise, we need to insert a new node.
      auto new_node = std::make_shared<CompactStringSet::Node>();
      new_node->letter = character;
      if (cur.lock()->child) {    // This node already has a child...
        cur = cur.lock()->child;  // ... so its child needs a sibling.
        while (cur.lock()->sibling)
          cur = cur.lock()->sibling;     // Find the last sibling...
        cur.lock()->sibling = new_node;  // ... and give it a new sibling.
      } else {
        cur.lock()->child = new_node;  // This node is childless. Let's give it one.
      }
      cur = new_node;
    }
  }
  if (!cur.lock()->terminal) {    // If the stopping point was not already marked as terminal...
    ++this->num_strings_;  // ... we inserted a new string
    cur.lock()->terminal = true;  // ... and the stopping point needs to be marked as such.
  }
}

bool CompactStringSet::find(const std::string& value) const {
  std::weak_ptr<CompactStringSet::Node> cur = this->root_ptr;  // Start at the dummy "root" node.
  for (auto character : value) {            // For each character...
    cur = this->find_next(cur, character);  // ... find a child of this node containing the char
    if (!cur.lock())
      return false;  // ... otherwise, this string must not be in the set
  }
  return cur.lock()->terminal;  // This set contains the string if the last char was marked as terminal
}

// Returns any child or sibling node representing the given char, or nullptr if none.
std::weak_ptr<CompactStringSet::Node> CompactStringSet::find_next(const std::weak_ptr<CompactStringSet::Node> base, char to_find) const {
  // If the node has a child...
  if (base.lock()->child) {
    // ... maybe the child has a matching char
    if (base.lock()->child->letter == to_find)
      return base.lock()->child;
    // ... or maybe one of their siblings does
    std::weak_ptr<CompactStringSet::Node> sibling = base.lock()->child->sibling;
    while (sibling.lock()) {
      if (sibling.lock()->letter == to_find)
        return sibling;
      sibling = sibling.lock()->sibling;
    }
  }
  std::weak_ptr<CompactStringSet::Node> ret;
  ret.reset();
  return ret;  // No match found
}

}  // namespace cs19