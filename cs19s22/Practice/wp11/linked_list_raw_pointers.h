/**
 * @file linked_list_raw_pointers.h
 *
 * The beginnings of a doubly linked list class, using raw pointers.
 *
 * @author Jeffrey Bergamini for CS 19, jbergamini@jeff.cis.cabrillo.edu
 */
#ifndef LINKED_LIST_RAW_POINTERS_H_
#define LINKED_LIST_RAW_POINTERS_H_

#include <initializer_list>
#include <iostream>

namespace cs19 {

/**
 * Class LinkedList is an archetypal doubly linked list. The public API exposes some standard list
 * operations. Node structures and internal list details are kept private.
 *
 * Also note that all member functions are defined inside the class declaration. (No separate .h and
 * .cpp/.cc files.) Template classes are usually defined this way.
 *
 * @tparam T type of the list elements
 */
template <typename T>
class LinkedList {
  struct Node;  // forward declaration for our private Node type

 public:
  /** Constructs a list with a copy of each of the elements in `init_list`, in the same order. */
  LinkedList(std::initializer_list<T> init_list) {
    this->operator=(init_list);  // call initializer list assignment
  }
  /** Destroys each of the contained elements, and deallocates all memory allocated by this list. */
  ~LinkedList() {
    // This print statement is only for demo purposes! Rarely/never should this actually be here.
    std::cerr << "List object at address " << this << " is about to die: " << *this << '\n';
    // This is the actual destructor:
    // while (this->head_) {            // As long as we have a pointer to a head node...
    //   Node* old_head = this->head_;  // ...keep a copy of it...
    //   this->head_ = old_head->next;  // ...point the head at the next node instead...
    //   delete old_head;               // ...and delete the node that used to be the head.
    // }
  }
  /** Removes last value from list. */
  void pop_back() {
    if (this->size_ == 1) {
      this->head_ = this->tail_ = nullptr;
    } else {
      Node* to_delete = this->tail_;
      this->tail_ = to_delete->prev;
      this->tail_->next = nullptr;
      delete to_delete; 
    }
    --this->size_;
  }
  /** Appends a copy of `val` to this list. */
  void push_back(const T& val) {
    Node* new_node = new Node{val};  // Must eventually be deleted in the destructor!
    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else {
      this->tail_->next = new_node;
      new_node->prev = this->tail_;
      this->tail_ = new_node;
    }
    ++this->size_;
  }
  /**  Prepends a copy of `val` to this list. */
  void push_front(const T& val) {
    Node* new_node = new Node{val};  // Must eventually be deleted in the destructor!
    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else {
      new_node->next = this->head_;
      this->head_->prev = new_node;
      this->head_ = new_node;
    }
    ++this->size_;
  }
  /** Replaces the contents of this list with a copy of each element in `init_list`. */
  LinkedList& operator=(std::initializer_list<T> init_list) {
    // We should empty the list first, but for now...
    this->size_ = 0;
    for (auto&& val : init_list)
      this->push_back(val);
    return *this;
  }
  /** Inserts this list into an ostream, with the format `[element1, element2, element3, ...]` */
  friend std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
    // "friend": This is not a member function of class LinkedList, but instead a global function
    // that has access to the private contents of any LinkedList, by virtue of being declared as a
    // friend of LinkedList.
    out << '[';
    for (Node* cur = list.head_; cur; cur = cur->next) {
      out << cur->data;
      if (cur->next)
        out << ", ";
    }
    out << ']';
    return out;  // Why?? (allows chaining of insertion operators)
  }

 private:
  struct Node {
    // Constructor(s)?
    // Other member functions?
    T data;  // Actual value for list element
    Node* next = nullptr;
    Node* prev = nullptr;
  };
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  std::size_t size_ = 0;
};

}  // namespace cs19

#endif  // LINKED_LIST_RAW_POINTERS_H_