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
#include <vector>
#include <queue>
#include <utility>

namespace cs19 {

bool CompactStringSet::insert(const std::string& value) {
  CompactStringSet::Node *cur = this->root_ptr.get();  // Start at the dummy "root" node.
  for (auto character : value) {                     // For each character...
    CompactStringSet::Node *search = this->find_next(cur, character);
    // ... find a child containing the character.
    if (search) {                                    // If such a node exists...
      cur = search;                                  // ... nothing to do. We just move on.
    } else {                                         // ... otherwise, we need to insert a new node.
      auto new_node = std::make_shared<CompactStringSet::Node>();
      new_node->letter = character;
      if (cur->child) {    // This node already has a child...
        cur = cur->child.get();  // ... so its child needs a sibling.
        while (cur->sibling)
          cur = cur->sibling.get();     // Find the last sibling...
        cur->sibling = new_node;  // ... and give it a new sibling.
      } else {
        cur->child = new_node;  // This node is childless. Let's give it one.
      }
      cur = new_node.get();
    }
  }
  if (!cur->terminal) {    // If the stopping point was not already marked as terminal...
    ++this->num_strings_;  // ... we inserted a new string
    cur->terminal = true;  // ... and the stopping point needs to be marked as such.
    return true;
  }
  return false;
}

bool CompactStringSet::find(const std::string& value) const {
  CompactStringSet::Node *cur = this->root_ptr.get();  // Start at the dummy "root" node.
  for (auto character : value) {            // For each character...
    cur = this->find_next(cur, character);  // ... find a child of this node containing the char
    if (!cur)
      return false;  // ... otherwise, this string must not be in the set
  }
  return cur->terminal;
  // This set contains the string if the last char was marked as terminal
}

bool CompactStringSet::erase(const std::string& value) {
  CompactStringSet::Node *cur = this->root_ptr.get();  // Start at the dummy "root" node.
  for (auto character : value) {            // For each character...
    cur = this->find_next(cur, character);  // ... find a child of this node containing the char
    if (!cur)
      return false;  // ... otherwise, this string must not be in the set
  }
  if (cur->terminal) {  // This set contains the string if the last char is terminal
    cur->terminal = false;
    --this->num_strings_;
    return true;
  }
  return false;
}

std::vector<std::string> CompactStringSet::autocomplete
  (const std::string& base, std::size_t n) const {
  std::vector<std::string> ret{};
  if (n < 1) {
    return ret;
  }
  // first find if base is in the set
  CompactStringSet::Node *cur = this->root_ptr.get();  // Start at the dummy "root" node.
  for (auto character : base) {            // For each character...
    cur = this->find_next(cur, character);  // ... find a child of this node containing the char
    if (!cur)
      return ret;  // ... otherwise, this string must not be in the set so return empty vector
  }
  std::queue<std::pair<std::string, CompactStringSet::Node * > > candidates;
  if (cur->child) {
    std::pair<std::string, CompactStringSet::Node * > to_add{base, cur->child.get()};
    candidates.push(to_add);
    cur = cur->child.get();
    while (cur->sibling) {
      to_add.second = cur->sibling.get();
      candidates.push(to_add);
      cur = cur->sibling.get();
    }
  }
  while (ret.size() < n && candidates.size() > 0) {
    auto to_eval = candidates.front();
    candidates.pop();
    std::string new_base = to_eval.first;
    new_base += to_eval.second->letter;
    if (to_eval.second->terminal == true) {
      ret.push_back(new_base);
    }
    if (to_eval.second->child.get()) {
      std::pair<std::string, CompactStringSet::Node * >
        to_add{new_base, to_eval.second->child.get()};
      candidates.push(to_add);
      while (to_add.second->sibling.get()) {
        to_add.second = to_add.second->sibling.get();
        candidates.push(to_add);
      }
    }
  }
  return ret;
}

// Returns any child or sibling node representing the given char, or nullptr if none.
CompactStringSet::Node * CompactStringSet::find_next
  (const CompactStringSet::Node *base, char to_find) const {
  // If the node has a child...
  if (base->child) {
    // ... maybe the child has a matching char
    if (base->child->letter == to_find)
      return base->child.get();
    // ... or maybe one of their siblings does
    CompactStringSet::Node *sibling = base->child->sibling.get();
    while (sibling) {
      if (sibling->letter == to_find)
        return sibling;
      sibling = sibling->sibling.get();
    }
  }
  return nullptr;  // No match found
}

}  // namespace cs19