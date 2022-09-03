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
  class Iterator;  // forward declaration for public Iterator type
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
  /**
   * @brief Constructs a list from a range.
   *
   * Constructs a list with as many elements as the range [first,last), with each element
   * constructed from its corresponding element in that range, in the same order.
   */
  template <typename InputIterator>
  LinkedList(InputIterator first, InputIterator last) {
    for (; first != last; ++first) this->push_back(*first);
  }
  /** Destroys each of the contained elements, and deallocates all memory allocated by this list. */
  ~LinkedList() {
    while (this->head_) {            // As long as we have a pointer to a head node...
      Node* old_head = this->head_;  // ...keep a copy of it...
      this->head_ = old_head->next;  // ...point the head at the next node instead...
      delete old_head;               // ...and delete the node that used to be the head.
    }
  }
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
    Node* new_node = new Node{val};
    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else {
      this->tail_->next = new_node;
      new_node->prev = this->tail_;
      this->tail_ = new_node;
    }
    ++this->size_;
  }
  /** Appends an empty node to this list. */
  void push_back() {
    Node* new_node = new Node;
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
    Node* new_node = new Node{val};
    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else {
      new_node->next = this->head_;
      this->head_->prev = new_node;
      this->head_ = new_node;
    }
    ++this->size_;
  }
  /** Removes first value from list. */
  void pop_front() {
    if (this->size_ == 0) {
      throw std::domain_error("Cannot remove a value from an empty list.");
    }
    Node* to_delete = this->head_;
    if (this->size_ == 1) {
      this->head_ = this->tail_ = nullptr;
    } else {
      this->head_ = to_delete->next;
      this->head_->prev = nullptr;
    }
    delete to_delete;
    --this->size_;
  }
  /** Removes last value from list. */
  void pop_back() {
    if (this->size_ == 0) {
      throw std::domain_error("Cannot remove a value from an empty list.");
    }
    Node* to_delete = this->tail_;
    if (this->size_ == 1) {
      this->head_ = this->tail_ = nullptr;
    } else {
      this->tail_ = to_delete->prev;
      this->tail_->next = nullptr;
    }
    delete to_delete;
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
    Node* current = this->head_;
    Node* to_delete = nullptr;
    while (current) {
      if (current->data == val) {
        to_delete = current;
        if (to_delete == this->head_) {
          to_delete = nullptr;
          this->pop_front();
          current = this->head_;
          continue;
        }
        if (to_delete == this->tail_) {
          to_delete = nullptr;
          this->pop_back();
          current = nullptr;
          break;
        }
      }
      current = current->next;
      if (to_delete) {
        current->prev = to_delete->prev;
        current->prev->next = current;
        --this->size_;
        delete to_delete;
        to_delete = nullptr;
      }
    }
  }
  /** Removes consecutive duplicate values from this list. */
  void unique() {
    if (this->size_ < 2) {
      return;
    }
    Node* current = this->head_;
    Node* compare = current->next;
    while (compare) {
      if (current->data == compare->data) {
        if (compare == this->tail_) {
          compare = nullptr;
          this->pop_back();
          break;
        }
        Node* to_delete = compare;
        compare = compare->next;
        current->next = compare;
        compare->prev = current;
        --this->size_;
        delete to_delete;
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
    Node* previous = this->head_;
    Node* current = previous->next;
    while (current) {
      std::swap(previous->prev, previous->next);
      previous = current;
      current = current->next;
    }
    std::swap(previous->prev, previous->next);
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
    Node* current = another.head_;
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
    Node* current1 = this->head_;
    Node* current2 = another.head_;
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
    for (Node* cur = list.head_; cur; cur = cur->next) {
      out << cur->data;
      if (cur->next)
        out << ", ";
    }
    out << ']';
    return out;  // Why?? (allows chaining of insertion operators)
  }
   /**
   * @brief Returns an iterator pointing to the first element in this list.
   *
   * Notice that, unlike `front()`, which returns a reference to the first element, this function
   * returns a bidirectional iterator pointing to it.
   *
   * If this list is empty, the returned iterator value shall not be dereferenced.
   *
   * @return An iterator to the beginning of the sequence.
   */
  Iterator begin() {
    Iterator start;
    start.current = this->head_;
    if (start.current == nullptr) {
      start.P = Iterator::none;
    } else {
      start.P = Iterator::middle;
    }
    return start;
  }

  /**
   * @brief Returns an iterator referring to the past-the-end element in this list.
   *
   * The past-the-end element is the theoretical element that would follow the last element in the
   * list. It does not point to any element, and thus shall not be dereferenced.
   *
   * Because the ranges used by functions of the standard library do not include the element pointed
   * by their closing iterator, this function is often used in combination with `begin()` to
   * specify a range including all the elements in the list.
   *
   * If this list is empty, this function returns the same as `begin()`.
   *
   * @return An iterator to the element past the end of the sequence.
   */
  Iterator end() {
    if (this->size_ == 0) {
      return this->begin();
    }
    Iterator finish;
    finish.current = this->tail_;
    finish.P = Iterator::after;
    return finish;
  }

  /**
   * Extends this list by inserting a new element before the element at the specified position.
   *
   * @param position Position in the list where the new element is inserted.
   * @param val Value to be copied to the inserted element.
   * @return An iterator that points to the newly inserted element.
   */
  Iterator insert(Iterator position, const T& val) {
    if (position.P == Iterator::before) {
      throw std::domain_error("Cannot insert an element before the before the beginning iterator.");
    }
    Node* new_node = new Node{val};
    if (this->size_ == 0) {
      this->head_ = this->tail_ = new_node;
    } else if (position.P == Iterator::after) {
      new_node->prev = position.current;
      new_node->next = nullptr;
      this->tail_->next = new_node;
      this->tail_ = new_node;
      position.current = new_node;
    } else if (position.P == Iterator::none) {
      throw std::domain_error("Cannot insert an element at a position that isn't in a list.");
    } else {
      if (this->head_ == position.current) {
        this->head_ = new_node;
      } else {
        position.current->prev->next = new_node;
      }
      new_node->prev = position.current->prev;
      position.current->prev = new_node;
      new_node->next = position.current;
    }
    ++this->size_;
    Iterator ret;
    ret.current = new_node;
    ret.P = Iterator::middle;
    return ret;
  }

  /**
   * Extends this list by inserting new elements before the element at the specified position.
   *
   * @param position Position in the list where the new elements are inserted.
   * @param n Number of elements to insert. Each element is initialized to a copy of `val`.
   * @param val Value to be copied to the inserted elements.
   * @return An iterator that points to the first of the newly inserted elements.
   */
  Iterator insert(Iterator position, std::size_t n, const T& val) {
    if (n < 1) {
      return position;
    }
    if (position.P == Iterator::before) {
      throw std::domain_error("Cannot insert new elments before the before the beg iterator.");
    }

    Iterator ret = this->insert(position, val);
    --n;
    if (position.P == Iterator::after) {
      position = this->end();
    }
    for (; n > 0; --n) {
      this->insert(position, val);
      if (position.P == Iterator::after) {
        position = this->end();
      }
    }
    return ret;
  }

  /**
   * Extends this list by inserting new elements in the range [first,last) before the element at the
   * specified position.
   *
   * @param position Position in the list where the new elements are inserted.
   * @param first An iterator that points to the first value to be inserted.
   * @param last An iterator that points to the value after the last value to be inserted.
   * @return An iterator that points to the first of the newly inserted elements.
   */
  template <typename InputIterator>
  Iterator insert(Iterator position, InputIterator first, InputIterator last) {
    if (first == last) {
      return position;
    }
    if (position.P == Iterator::before) {
      throw std::domain_error("Cannot insert a range before the before the start iterator.");
    }
    Iterator ret = this->insert(position, first.current->data);
    ++first;
    for (; first != last; ++first) {
      this->insert(position, first.current->data);
    }
    return ret;
  }

  /**
   * Extends this list by inserting new elements from an initializer list at the specified position.
   *
   * @param position Position in the list where the new elements are inserted.
   * @param init_list The list of values to be inserted.
   * @return An iterator that points to the first of the newly inserted elements.
   */
  Iterator insert(Iterator position, std::initializer_list<T> init_list) {
    if (position.P == Iterator::before) {
      throw std::domain_error("Cannot insert a value before the before the start iterator.");
    }
    if (position.P == Iterator::after) {
      position = this->end();
    }
    auto list_iterator = init_list.begin();
    Iterator ret = this->insert(position, *list_iterator);
    ++list_iterator;
    for (; list_iterator != init_list.end(); list_iterator++){
      this->insert(position, *list_iterator);
      if (position.P == Iterator::after) {
        position = this->end();
      }
    }
    return ret;
  }

  /**
   * Removes from this list a single element at the specified position.
   *
   * @param position Iterator pointing to a single element to be removed from the list.
   * @return An iterator pointing to the element that followed the last element erased by the
   * function call. This is the list end if the operation erased the last element in the
   * sequence.
   */
  Iterator erase(Iterator position) {
    if (position.P != Iterator::middle) {
      throw std::domain_error("Cannot erase a node that isn't in the list.");
    }
    Iterator ret = position;
    ++ret;
    if (position.current == this->head_ && position.current == this->tail_) {
      this->head_ = this->tail_ = nullptr;
      ret.current = nullptr;
      ret.P = Iterator::none;
    } else if (position.current == this->head_) {
      this->head_ = ret.current;
      ret.current->prev = nullptr;
    } else if (position.current == this->tail_) {
      this->tail_ = position.current->prev;
      position.current->prev->next = nullptr;
    } else {
      position.current->prev->next = ret.current;
      ret.current->prev = position.current->prev;
    }
    delete position->current;
    position.current = nullptr;
    position.P = Iterator::none;
    --this->size_;
    if (ret.P == Iterator::after) {
      ret.current = this->tail_;
    }
    return ret;
  }

  /**
   * removes from this list a range of elements (`[first,last)`).
   *
   * @param first An iterator that points to the first value to be removed.
   * @param last An iterator that points to the value after the last value to be removed.
   * @return An iterator pointing to the element that followed the last element erased by the
   * function call. This is the list end if the operation erased the last element in the sequence.
   */
  Iterator erase(Iterator first, Iterator last) {
    while (first != last) {
      first = this->erase(first);
    }
    // return (last == this->end()) ? this->end() : last;
    return last;
  }

  /**
   * Transfers all elements from another list into this list, inserting them at `position`. The
   * operation does not involve the construction or destruction of any element.
   *
   * @param position An iterator that points to the position in this list where elements are
   * inserted.
   * @param that The list from which to copy elements.
   */
  void splice(Iterator position, LinkedList& that) {
    if (that.size_ == 0) {
      return;
    }
    if (this->size_ == 0) {
      this->head_ = that.head_;
      this->tail_ = that.tail_;
      that.tail_->next = nullptr;
      that.head_->prev = nullptr;
      that.head_ = nullptr;
      that.tail_ = nullptr;
      this->size_ = that.size_;
      that.size_ = 0;
      return;
    }
    if (position.P == Iterator::before || position.P == Iterator::none) {
      throw std::domain_error("Cannot insert before the before the beginning iterator.");
    }
    if (position.current->prev == nullptr) {  // if it's the new head, set as such
      this->head_ = that.head_;
      that.head_->prev = nullptr;
      position.current->prev = that.tail_;
      that.tail_->next = position.current;
    } else if (position.P == Iterator::after) {  // if it's the new tail, set as such
      this->tail_->next = that.head_;
      this->tail_ = that.tail_;
      that.tail_->next = nullptr;
      that.head_->prev = position.current;
    } else {
      position.current->prev->next = that.head_;
      that.head_->prev = position.current->prev;
      position.current->prev = that.tail_;
      that.tail_->next = position.current;
    }
    // repair that
    this->size_ += that.size_;
    that.head_ = nullptr;
    that.tail_ = nullptr;
    that.size_ = 0;
  }

  /**
   * Transfers one element from another list into this list, inserting it at `position`. The
   * operation does not involve the construction or destruction of any element.
   *
   * @param position An iterator that points to the insertion position in this list.
   * @param that The list from which to copy an element.
   * @param that_position An iterator that points to the element to transfer from the other list to
   * this list.
   */
  void splice(Iterator position, LinkedList& that, Iterator that_position) {
    if (that_position->P != Iterator::middle) {
      return;
    }
    if (that.size_ == 0) {
      return;
    }
    if (that_position.current->prev == nullptr) {  // if it was the head, adjust head
      that.head_ = that_position.current->next;
    } else {
      that_position.current->prev->next = that_position.current->next;
    }
    if (that_position.current->next == nullptr) {  // if it was the tail, adjust tail
      that.tail_ = that_position.current->prev;
    } else {
      that_position.current->next->prev = that_position.current->prev;
    }
    // that should now be stitched back together
    --that.size_;
    ++this->size_;
    if (this->size_ == 1) {
      this->head_ = this->tail_ = that_position.current;
      that_position.current->next = nullptr;
      that_position.current->prev = nullptr;
      return;
    }
    if (position.P == Iterator::before || position.P == Iterator::none) {
      throw std::domain_error("Cannot insert before the before the beginning iterator.");
    }
    if (position.current->prev == nullptr) {  // if it's the new head, set head to point to it
      this->head_ = that_position.current;
      that_position.current->prev = nullptr;
    } else {
      position.current->prev->next = that_position.current;
      that_position.current->prev = position.current->prev;
    }
    if (position.P == Iterator::after) {  // if it's the new tail, set as such
      this->tail_ = that_position.current;
      that_position.current->next = nullptr;
    } else {
      position.current->prev = that_position.current;
      that_position.current->next = position.current;
    }
  }

  /**
   * Transfers the range of elements `[first,last)` from another list into this list, inserting it
   * at `position`. The operation does not involve the construction or destruction of any element.
   *
   * @param position An iterator that points to the insertion position in this list.
   * @param that The list from which to copy a range of elements.
   * @param first An iterator that points to the first value to be transferred.
   * @param last An iterator that points to the value after the last value to be transferred.
   */
  void splice(Iterator position, LinkedList& that, Iterator first, Iterator last) {
    while (first != last) {
      Iterator to_insert = first;
      ++first;
      this->splice(position, that, to_insert);
    }
  }

  class Iterator {
   public:
    friend class LinkedList;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = int;
    using pointer = T*;
    using reference = T&;
    // Default constructor
    Iterator() = default;
    // Copy constructor
    Iterator(const Iterator& other) {
      this->operator=(other);
    }
    // I also have another constructor, FYI
    // Destructor, if necessary
    // ~Iterator() { /* TBD */ }
    // Copy assign
    Iterator& operator=(const Iterator& that) {
      this->current = that.current;
      this->P = that.P;
      return *this;
    }
    // Prefix increment
    Iterator& operator++() {
      if (this->P == Iterator::before) {
        this->P = Iterator::middle;
        return *this;
      }
      if (this->P == Iterator::after) {
        throw std::domain_error("Cannot increment an off the end list iterator.");
      }
      if (this->P == Iterator::none) {
        throw std::domain_error("Cannot increment a list iterator to an empty list.");
      }
      if (this->current->next == nullptr) {
        this->P = Iterator::after;
        return *this;
      }
      this->current = this->current->next;
      return *this;
    }
    // Postfix increment
    Iterator operator++(int) {
      Iterator tmp(*this);
      this->operator++();
      return tmp;
    }
    // Prefix decrement
    Iterator& operator--() {
      if (this->P == Iterator::after) {
        this->P = Iterator::middle;
        return *this;
      }
      if (this->P == Iterator::before) {
        throw std::domain_error("Cannot decrement an off the beginning list iterator.");
      }
      if (this->P == Iterator::none) {
        throw std::domain_error("Cannot decrement a list iterator to an empty list.");
      }
      if (this->current->prev == nullptr) {
        this->P = before;
        return *this;
      }
      this->current = this->current->prev;
      return *this;
    }
    // Postfix decrement
    Iterator operator--(int) {
      Iterator tmp(*this);
      this->operator--();
      return tmp;
    }
    // Inequality
    bool operator!=(const Iterator &that) const { return !(this->operator==(that)); }
    // Equality
    bool operator==(const Iterator &that) const {
      if (this->P == Iterator::after && that.P == Iterator::after) {
        return true;
      }
      return this->current == that.current && this->P == that.P;
    }
    // lvalue dereference
    T& operator*() const {
      if (this->P == Iterator::none) {
        return this->dummy;
      }
      return this->current->data;
    }
    // referring
    Iterator* operator->() { return this; }

   private:
    Node* current;
    enum Position {none, before, middle, after};
    Position P = none;
    mutable T dummy = {};
    // FYI, I have two member variables in my class: a Node* and a bool
  };

 private:
  struct Node {
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