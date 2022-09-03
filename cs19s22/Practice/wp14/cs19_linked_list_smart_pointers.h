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
#include <utility>
#include <stdexcept>
#include <memory>

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
  /** Default Constructor */
  LinkedList() = default;
  /** Constructs a list with a copy of each of the elements in `init_list`, in the same order. */
  LinkedList(std::initializer_list<T> init_list) {
    this->operator=(init_list);  // call initializer list assignment
  }
  /** Constructs a linked list with a copy of each of the elements in `another`,
   * in the same order */
  LinkedList(const LinkedList &another) {
    this->operator=(another);
  }
  /** Destroys each of the contained elements, and deallocates all memory allocated by this list. */
  /* Now that we're using smart pointers shouldn't need this anymore.
  ~LinkedList() {
    while (this->head_) {            // As long as we have a pointer to a head node...
      Node* old_head = this->head_;  // ...keep a copy of it...
      this->head_ = old_head->next;  // ...point the head at the next node instead...
      delete old_head;               // ...and delete the node that used to be the head.
    }
  }
  */
  /** Returns the number of elements in this list. */
  std::size_t size() const {
    return this->size_;
  }
  /** Returns whether the list is empty. */
  bool empty() const {
    return this->size_ == 0 ? true : false;
  }
  /** Returns a reference to the value in the first element. */
  T& front() const {
    if (this->size_ == 0) {
      throw std::domain_error("Cannot return a reference to a value in an empty list.");
    }
    return this->head_->data;
  }
  /** Returns a reference to the value in the last element. */
  T& back() const {
    if (this->size_ == 0) {
      throw std::domain_error("Cannot return a reference to a value in an empty list.");
    }
    return this->tail_->data;
  }
  /** Appends a copy of `val` to this list. */
  void push_back(const T& val) {
    auto new_node = std::make_shared<Node>(val);
    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else {
      this->tail_->next = new_node;
      new_node->prev = std::weak_ptr<Node>(this->tail_);
      this->tail_ = new_node;
    }
    ++this->size_;
  }
  /** Appends an empty node to this list. */
  void push_back() {
    auto new_node = std::make_shared<Node>();
    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else {
      this->tail_->next = new_node;
      new_node->prev = std::weak_ptr<Node>(this->tail_);
      this->tail_ = new_node;
    }
    ++this->size_;
  }
  /**  Prepends a copy of `val` to this list. */
  void push_front(const T& val) {
    auto new_node = std::make_shared<Node>(val);
    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else {
      new_node->next = this->head_;
      this->head_->prev = std::weak_ptr<Node>(new_node);
      this->head_ = new_node;
    }
    ++this->size_;
  }
  /** Removes first value from list. */
  void pop_front() {
    if (this->size_ == 0) {
      // raise std::domain_error
    }
    if (this->size_ == 1) {
      this->head_ = this->tail_ = nullptr;
    } else {
      this->head_ = this->head_->next;
      this->head_->prev.reset();
    }
    --this->size_;
  }
  /** Removes last value from list. */
  void pop_back() {
    if (this->size_ == 0) {
      // raise std::domain_error
    }
    if (this->size_ == 1) {
      this->head_ = this->tail_ = nullptr;
    } else {
      this->tail_ = this->tail_->prev.lock();
      this->tail_->next = nullptr;
    }
    --this->size_;
  }
  /** Resizes the list so that it contains n elements. If n is smaller than the current
   * list size, the content is reduced to its first n elements, removing those beyond.
   * if n is greater than the current list size the content is expanded by inserting at
   * the end as many elements as needed to reach a size of n. */
  void resize(std::size_t n) {
    if (n > this->size_) {
      while (n > this->size_) {
        this->push_back();
      }
    } else if (n < this->size_) {
      while (n < this->size_) {
        this->pop_back();
      }
    }
    return;
  }
  /** Resizes the list so that it contains n elements. If n is smaller than the current
   * list size, the content is reduced to its first n elements, removing those beyond.
   * if n is greater than the current list size the content is expanded by inserting at
   * the end as many elements as needed to reach a size of n, with a value of fill_value. */
  void resize(std::size_t n, const T& fill_value) {
    if (n > this->size_) {
      while (n > this->size_) {
        this->push_back(fill_value);
      }
    } else if (n < this->size_) {
      while (n < this->size_) {
        this->pop_back();
      }
    }
    return;
  }
  /** Deletes all values in this list. */
  void clear() {
    while (this->size_ > 0) {
      this->pop_back();
    }
  }
  /** Removes from the container all the elements that compare equal to val. */
  void remove(const T &val) {
    if (this->size_ == 0) {
      return;
    }
    auto current = this->head_;
    while (current) {
      if (current->data == val) {
        if (current == this->head_) {
          this->pop_front();
          current = this->head_;
          continue;
        }
        if (current == this->tail_) {
          this->pop_back();
          current = nullptr;
          break;
        }
        current->next->prev = current->next->prev.lock()->prev;
        current->next->prev.lock()->next = current->next;
        --this->size_;
      }
      current = current->next;
    }
  }
  /** Removes consecutive duplicate values from this list. */
  void unique() {
    if (this->size_ < 2) {
      return;
    }
    auto current = this->head_;
    auto compare = current->next;
    while (compare) {
      if (current->data == compare->data) {
        if (compare == this->tail_) {
          compare = nullptr;
          this->pop_back();
          break;
        }
        compare = compare->next;
        current->next = compare;
        compare->prev = current;
        --this->size_;
      } else {
        current = compare;
        compare = compare->next;
      }
    }
  }
  /** Reverses the order of elements in this list. */
  void reverse() {
    if (this->size_ < 2) {
      return;
    }
    auto previous = this->head_;
    auto current = previous->next;
    while (current) {
      auto temp = previous->prev;
      previous->prev = previous->next;
      previous->next = temp.lock();
      previous = current;
      current = current->next;
    }
    auto temp = previous->prev;
    previous->prev = previous->next;
    previous->next = temp.lock();
    std::swap(this->head_, this->tail_);
  }
  /** Replaces the contents of this list with a copy of each element in `init_list`. */
  LinkedList& operator=(std::initializer_list<T> init_list) {
    this->clear();
    for (auto&& val : init_list)
      this->push_back(val);
    return *this;
  }
  /** Replaces the contents of this list with a copy of each element in another
   * in the same order. */
  LinkedList& operator=(const LinkedList &another) {
    this->clear();
    auto current = another.head_;
    while (current) {
      this->push_back(current->data);
      current = current->next;
    }
    return *this;
  }
  /** Compares this list with another for equality. */
  bool operator==(const LinkedList &another) {
    if (this->size_ != another.size_) {
      return false;
    }
    auto current1 = this->head_;
    auto current2 = another.head_;
    while (current1) {
      if (current1->data != current2->data) {
        return false;
      }
      current1 = current1->next;
      current2 = current2->next;
    }
    return true;
  }
  /** Compares this list with another for inequality. */
  bool operator!=(const LinkedList &another) {
    return !(this->operator==(another));
  }
  /** Inserts this list into an ostream, with the format `[element1, element2, element3, ...]` */
  friend std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
    // "friend": This is not a member function of class LinkedList, but instead a global function
    // that has access to the private contents of any LinkedList, by virtue of being declared as a
    // friend of LinkedList.
    out << '[';
    for (auto cur = list.head_; cur; cur = cur->next) {
      out << cur->data;
      if (cur->next)
        out << ", ";
    }
    out << ']';
    return out;  // Why?? (allows chaining of insertion operators)
  }

 private:
  struct Node {
    Node() = default;
    Node(T data) : data(data) {
      // don't need to write code here
    }
    T data;  // Actual value for list element
    std::shared_ptr<Node> next = nullptr;
    std::weak_ptr<Node> prev;
  };
  std::shared_ptr<Node> head_ = nullptr;
  std::shared_ptr<Node> tail_ = nullptr;
  std::size_t size_ = 0;
};

}  // namespace cs19

#endif  // LINKED_LIST_RAW_POINTERS_H_