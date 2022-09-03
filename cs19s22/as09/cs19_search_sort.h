#ifndef CS19_SEARCH_SORT_H_
#define CS19_SEARCH_SORT_H_

/**
 * Namespace cs19 contains functions for our search and sort assignment.
 *
 * @author Karen Corscadden for CS 19, kmcorscadden@jeff.cis.cabrillo.edu
 */
namespace cs19 {

/**
 * Swaps two values
 */
template<typename T>
void swap(T &t1, T &t2) {
  T temp = t1;
  t1 = t2;
  t2 = temp;
}

/**
 * Returns an iterator to the first element in the range `[first,last)` that compares equal to
 * `val`. If no such element is found, the function returns `last`.
 *
 * @tparam Iterator a position iterator that supports the [standard input iterator
 * operations](http://www.cplusplus.com/reference/iterator/InputIterator/)
 * @tparam Value a value type that supports `operator==`
 *
 * @param first the initial position in the sequence to be sorted
 * @param last one element past the final position in the sequence to be sorted
 * @param val the value for which to search
 * @return an iterator to the first element in the range that compares equal to `val`. If no
 * elements match, the function returns `last`.
 */
template <typename Iterator, typename Value>
Iterator linear_search(Iterator first, Iterator last, const Value &val) {
  for (Iterator current = first; current != last; current++) {
    if (*current == val) {
      return current;
    }
  }
  return last;
}

/**
 * Performs an index-based linear search on an indexable object for a given value.
 *
 * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
 * elements must be of template type `Value`.
 * @tparam Value a value type that supports `operator==`
 *
 * @param haystack the object to search
 * @param needle the value for which to search
 * @return the first index found via linear search at which `haystack` contains `needle`, or `-1` if
 * `haystack` does not contain `needle`
 */
template <typename IndexedContainer, typename Value>
int linear_search(const IndexedContainer &haystack, const Value &needle) {
  unsigned size = static_cast<unsigned>(haystack.size());
  for (unsigned i = 0; i < size; i++) {
    if (haystack[i] == needle) {
      return i;
    }
  }
  return -1;
}

/**
 * Performs an index-based binary search on an indexable object for a given value.
 *
 * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
 * elements must be of template type `Value`.
 * @tparam Value a value type that supports `operator==` and `operator<`
 *
 * @param haystack the object to search
 * @param needle the value for which to search
 * @return the first index found via binary search at which `haystack` contains `needle`, or `-1` if
 * `haystack` does not contain `needle`
 */
template <typename IndexedContainer, typename Value>
int binary_search(const IndexedContainer &haystack, const Value &needle) {
  int left = 0;
  int right = static_cast<int>(haystack.size()) - 1;
  int mid = (right + left) / 2;
  if (right < 0) {
    return -1;
  }
  while (left <= right) {
    mid = (right + left) / 2;
    if (haystack[mid] == needle) {
      return mid;
    } else if (haystack[mid] < needle) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

/**
 * Performs an index-based bubble sort on any indexable container object.
 *
 * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
 * elements must support `operator<` and `operator=`.
 *
 * @param values the object to sort
 */
template <typename IndexedContainer>
void bubble_sort(IndexedContainer &values) {
  unsigned size = static_cast<unsigned>(values.size());
  bool swapped = false;
  do {
    swapped = false;
    for (unsigned i = 0; i < size - 1; i++) {
      if (values[i + 1] < values[i]) {
        swap(values[i + 1], values[i]);
        swapped = true;
      }
    }
  } while (swapped);
}

/**
 * Sorts the elements in the range `[first,last)` into ascending order, using the bubble-sort
 * algorithm. The elements are compared using `operator<`.
 *
 * @tparam Iterator a position iterator that supports the [standard bidirectional iterator
 * operations](http://www.cplusplus.com/reference/iterator/BidirectionalIterator/)
 *
 * @param first the initial position in the sequence to be sorted
 * @param last one element past the final position in the sequence to be sorted
 */
template <typename Iterator>
void bubble_sort(Iterator first, Iterator last) {
  if (first == last) {
    return;
  }
  bool swapped = false;
  do {
    swapped = false;
    Iterator next = first;
    next++;
    for (Iterator current = first; next != last; current++, next++) {
      if (*next < *current) {
        swap(*next, *current);
        swapped = true;
      }
    }
  } while (swapped);
}

/**
 * Performs an index-based selection sort on an indexable object.
 *
 * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
 * elements must support `operator<` and `operator=`.
 *
 * @param values the object to sort
 */
template <typename IndexedContainer>
void selection_sort(IndexedContainer &values) {
  unsigned size = static_cast<unsigned>(values.size());
  unsigned lowest = 0;
  for (unsigned first = 0; first < size - 1; first++) {
    lowest = first;
    for (unsigned check = first + 1; check < size; check++) {
      if (values[check] < values[lowest]) {
        lowest = check;
      }
    }
    swap(values[first], values[lowest]);
  }
}

/**
 * Sorts the elements in the range `[first,last)` into ascending order, using the selection-sort
 * algorithm.
 *
 * @tparam Iterator a position iterator that supports the [standard input iterator
 * operations](http://www.cplusplus.com/reference/iterator/InputIterator/)
 *
 * @param first the initial position in the sequence to be sorted
 * @param last one element past the final position in the sequence to be sorted
 */
template <typename Iterator>
void selection_sort(Iterator first, Iterator last) {
  if (first == last) {
    return;
  }

  Iterator lowest = first;
  Iterator next = first;
  next++;
  if (next == last) {
    return;
  }

  for (Iterator unsorted = first; next != last; unsorted++, next++) {
    lowest = unsorted;
    for (Iterator check = next; check != last; check++) {
      if (*check < *lowest) {
        lowest = check;
      }
    }
    swap(*unsorted, *lowest);
  }
}

}  // namespace cs19

#endif  // CS19_SEARCH_SORT_H_
