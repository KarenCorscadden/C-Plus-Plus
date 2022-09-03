/**
 * @file cs19_linked_list_raw_pointers_iterable_test.cpp
 *
 * Testing the iterator-based functions in cs19::LinkedList.
 *
 * @author Jeffrey Bergamini for CS 19, jbergamini@jeff.cis.cabrillo.edu
 */
#include <algorithm>
#include <cassert>
#include <iterator>
#include <list>
#include "cs19_linked_list_raw_pointers_iterable.h"
// #include "cs19_linked_list.h"

template <typename T>
void compare_lists(std::list<T>& stl_list, cs19::LinkedList<T>& our_list) {
  std::copy(stl_list.begin(), stl_list.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;
  std::copy(our_list.begin(), our_list.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;
  assert(stl_list.size() == our_list.size());
  auto stl_iterator = stl_list.begin();
  auto our_iterator = our_list.begin();
  while (our_iterator != our_list.end() and stl_iterator != stl_list.end()) {
    assert(*our_iterator++ == *stl_iterator++);
  }
  assert(our_iterator == our_list.end() and stl_iterator == stl_list.end());
}

int main() {
  std::list<int> stl_list{1, 2, 3, 4, 5};
  cs19::LinkedList<int> our_list{1, 2, 3, 4, 5};

  auto stl_iterator = stl_list.begin();
  auto our_iterator = our_list.begin();
  while (our_iterator != our_list.end() and stl_iterator != stl_list.end()) {
    our_list.insert(our_iterator, 10);
    stl_list.insert(stl_iterator, 10);
    compare_lists(stl_list, our_list);
    ++our_iterator;
    ++stl_iterator;
  }

  stl_list.insert(stl_iterator, std::size_t(5), 99);
  our_list.insert(our_iterator, std::size_t(5), 99);
  compare_lists(stl_list, our_list);

  assert(stl_iterator == stl_list.end());
  assert(our_iterator == our_list.end());

  stl_list.insert(stl_iterator, {2, 4, 6, 0, 1});
  our_list.insert(our_iterator, {2, 4, 6, 0, 1});
  compare_lists(stl_list, our_list);

  stl_iterator = stl_list.begin();
  our_iterator = our_list.begin();
  stl_list.erase(stl_iterator);
  our_list.erase(our_iterator);
  compare_lists(stl_list, our_list);

  stl_iterator = stl_list.begin();
  our_iterator = our_list.begin();
  std::advance(stl_iterator, stl_list.size() / 2);
  std::advance(our_iterator, our_list.size() / 2);
  stl_list.erase(stl_iterator);
  our_list.erase(our_iterator);
  compare_lists(stl_list, our_list);

  stl_iterator = stl_list.end();
  --stl_iterator;
  our_iterator = our_list.end();
  --our_iterator;
  stl_list.erase(stl_iterator);
  our_list.erase(our_iterator);
  compare_lists(stl_list, our_list);

  auto stl_start_erase = stl_list.begin();
  auto our_start_erase = our_list.begin();
  std::advance(stl_start_erase, 9);
  std::advance(our_start_erase, 9);
  auto stl_end_erase = stl_start_erase;
  auto our_end_erase = our_start_erase;
  std::advance(stl_end_erase, 4);
  std::advance(our_end_erase, 4);
  stl_list.erase(stl_start_erase, stl_end_erase);
  our_list.erase(our_start_erase, our_end_erase);
  compare_lists(stl_list, our_list);

  std::list<int> stl_donation{100, 200, 300};
  cs19::LinkedList<int> our_donation{100, 200, 300};
  stl_iterator = stl_list.begin();
  our_iterator = our_list.begin();
  std::advance(stl_iterator, stl_list.size() / 2);
  std::advance(our_iterator, our_list.size() / 2);
  stl_list.splice(stl_iterator, stl_donation);
  our_list.splice(our_iterator, our_donation);
  compare_lists(stl_list, our_list);
  assert(stl_donation.size() == our_donation.size());

  stl_donation = {500, 600, 700};
  our_donation = {500, 600, 700};
  stl_iterator = stl_list.begin();
  our_iterator = our_list.begin();
  std::advance(stl_iterator, stl_list.size() / 2);
  std::advance(our_iterator, our_list.size() / 2);
  stl_list.splice(stl_iterator, stl_donation, stl_donation.begin());
  our_list.splice(our_iterator, our_donation, our_donation.begin());
  compare_lists(stl_list, our_list);
  assert(stl_donation.size() == our_donation.size());

  stl_donation = {1000, 2000, 3000, 4000, 5000, 6000, 7000};
  our_donation = {1000, 2000, 3000, 4000, 5000, 6000, 7000};
  auto stl_donation_start = stl_donation.begin();
  auto our_donation_start = our_donation.begin();
  std::advance(stl_donation_start, 2);
  std::advance(our_donation_start, 2);
  auto stl_donation_stop = stl_donation_start;
  auto our_donation_stop = our_donation_start;
  std::advance(stl_donation_stop, 3);
  std::advance(our_donation_stop, 3);
  stl_list.splice(stl_iterator, stl_donation, stl_donation_start, stl_donation_stop);
  our_list.splice(our_iterator, our_donation, our_donation_start, our_donation_stop);
  compare_lists(stl_list, our_list);
  assert(stl_donation.size() == our_donation.size());

  {
    std::list<int> stl_list2{1};
    cs19::LinkedList<int> our_list2{1};

    std::list<int> stl_donation2{2};
    cs19::LinkedList<int> our_donation2{2};

    stl_list2.splice(stl_list2.begin(), stl_donation2);
    our_list2.splice(our_list2.begin(), our_donation2);

    compare_lists(stl_list2, our_list2);
  }

  {
    std::list<int> stl_list2{1, 2};
    cs19::LinkedList<int> our_list2{1, 2};

    std::list<int> stl_donation2{3};
    cs19::LinkedList<int> our_donation2{3};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();
    std::advance(stl_list2_start, 1);
    std::advance(our_list2_start, 1);

    stl_list2.splice(stl_list2_start, stl_donation2);
    our_list2.splice(our_list2_start, our_donation2);

    compare_lists(stl_list2, our_list2);
  }

  {
    std::list<int> stl_list2{1, 2};
    cs19::LinkedList<int> our_list2{1, 2};

    std::list<int> stl_donation2{3};
    cs19::LinkedList<int> our_donation2{3};

    stl_list2.splice(stl_list2.end(), stl_donation2);
    our_list2.splice(our_list2.end(), our_donation2);

    compare_lists(stl_list2, our_list2);
  }

  {
    std::list<int> stl_list2{};
    cs19::LinkedList<int> our_list2{};

    std::list<int> stl_donation2{2};
    cs19::LinkedList<int> our_donation2{2};

    stl_list2.splice(stl_list2.begin(), stl_donation2);
    our_list2.splice(our_list2.begin(), our_donation2);

    compare_lists(stl_list2, our_list2);
  }

  {
    std::list<int> stl_list2{1};
    cs19::LinkedList<int> our_list2{1};

    stl_list2.erase(stl_list2.begin());
    our_list2.erase(our_list2.begin());

    compare_lists(stl_list2, our_list2);
  }

  if (0) {
    std::list<int> stl_list2{1};
    cs19::LinkedList<int> our_list2{1};

    stl_list2.erase(stl_list2.end());
    our_list2.erase(our_list2.end());

    compare_lists(stl_list2, our_list2);
  }

  {
    std::list<int> stl_list2{1, 2, 3};
    cs19::LinkedList<int> our_list2{1, 2, 3};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();

    stl_list2.erase(stl_list2_start);
    our_list2.erase(our_list2_start);

    compare_lists(stl_list2, our_list2);
  }

  {
    std::list<int> stl_list2{1, 2, 3};
    cs19::LinkedList<int> our_list2{1, 2, 3};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();
    std::advance(stl_list2_start, 1);
    std::advance(our_list2_start, 1);

    stl_list2.erase(stl_list2_start);
    our_list2.erase(our_list2_start);

    compare_lists(stl_list2, our_list2);
  }

  {
    std::list<int> stl_list2{1, 2, 3};
    cs19::LinkedList<int> our_list2{1, 2, 3};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();
    std::advance(stl_list2_start, 2);
    std::advance(our_list2_start, 2);

    stl_list2.erase(stl_list2_start);
    our_list2.erase(our_list2_start);

    compare_lists(stl_list2, our_list2);
  }

  if (0) {
    std::list<int> stl_list2{};
    cs19::LinkedList<int> our_list2{};

    stl_list2.erase(stl_list2.begin());
    our_list2.erase(our_list2.begin());

    compare_lists(stl_list2, our_list2);
  }

  // check return pointers from erase
  { // delete first element in 1 length list
    std::list<int> stl_list2{1};
    cs19::LinkedList<int> our_list2{1};

    auto stl_return = stl_list2.erase(stl_list2.begin());
    auto our_return = our_list2.erase(our_list2.begin());
    if (stl_return == stl_list2.end()) {
      std::cout << "true1" << std::endl;
    } else {
      std::cout << "false1" << std::endl;
    }
    if (our_return == our_list2.end()) {
      std::cout << "pass1" << std::endl;
    } else {
      std::cout << "fail1" << std::endl;
    }

    if (*our_return == *stl_return) {
      std::cout << "*pass1" << std::endl;
    } else {
      std::cout << "*fail1" << std::endl;
    }

    compare_lists(stl_list2, our_list2);

    std::cout << *stl_return << std::endl;
    std::cout << *our_return << std::endl;
    std::cout << std::endl;
  }

  { // delete first element in 3 length list
    std::list<int> stl_list2{1, 2, 3};
    cs19::LinkedList<int> our_list2{1, 2, 3};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();

    auto stl_return = stl_list2.erase(stl_list2_start);
    auto our_return = our_list2.erase(our_list2_start);
    if (stl_return == stl_list2.begin()) {
      std::cout << "true2" << std::endl;
    } else {
      std::cout << "false2" << std::endl;
    }
    if (our_return == our_list2.begin()) {
      std::cout << "pass2" << std::endl;
    } else {
      std::cout << "fail2" << std::endl;
    }
    if (*our_return == *stl_return) {
      std::cout << "*pass2" << std::endl;
    } else {
      std::cout << "*fail2" << std::endl;
    }
    if (*stl_return == *our_return) {
      std::cout << "*pass2" << std::endl;
    } else {
      std::cout << "*fail2" << std::endl;
    }

    compare_lists(stl_list2, our_list2);
  }

  { // delete second element in 3 length list
    std::list<int> stl_list2{1, 2, 3};
    cs19::LinkedList<int> our_list2{1, 2, 3};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();
    std::advance(stl_list2_start, 1);
    std::advance(our_list2_start, 1);

    auto stl_return = stl_list2.erase(stl_list2_start);
    auto our_return = our_list2.erase(our_list2_start);

    auto stl_list2_check = stl_list2.begin();
    auto our_list2_check = our_list2.begin();
    std::advance(stl_list2_check, 1);
    std::advance(our_list2_check, 1);

    if (stl_return == stl_list2_check) {
      std::cout << "true3" << std::endl;
    } else {
      std::cout << "false3" << std::endl;
    }
    if (our_return == our_list2_check) {
      std::cout << "pass3" << std::endl;
    } else {
      std::cout << "fail3" << std::endl;
    }
    if (*our_return == *stl_return) {
      std::cout << "*pass3" << std::endl;
    } else {
      std::cout << "*fail3" << std::endl;
    }

    compare_lists(stl_list2, our_list2);
  }

  { // delete last element in 3 length list
    std::list<int> stl_list2{1, 2, 3};
    cs19::LinkedList<int> our_list2{1, 2, 3};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();
    std::advance(stl_list2_start, 2);
    std::advance(our_list2_start, 2);

    auto stl_return = stl_list2.erase(stl_list2_start);
    auto our_return = our_list2.erase(our_list2_start);

    if (stl_return == stl_list2.end()) {
      std::cout << "true4" << std::endl;
    } else {
      std::cout << "false4" << std::endl;
    }
    if (our_return == our_list2.end()) {
      std::cout << "pass4" << std::endl;
    } else {
      std::cout << "fail4" << std::endl;
    }
    if (*our_return == *stl_return) {
      std::cout << "*pass4" << std::endl;
    } else {
      std::cout << "*fail4" << std::endl;
    }

    compare_lists(stl_list2, our_list2);
  }

  { // delete last element in 2 length list
    std::list<int> stl_list2{1, 2};
    cs19::LinkedList<int> our_list2{1, 2};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();
    std::advance(stl_list2_start, 1);
    std::advance(our_list2_start, 1);

    auto stl_return = stl_list2.erase(stl_list2_start);
    auto our_return = our_list2.erase(our_list2_start);

    if (stl_return == stl_list2.end()) {
      std::cout << "true5" << std::endl;
    } else {
      std::cout << "false5" << std::endl;
    }
    if (our_return == our_list2.end()) {
      std::cout << "pass5" << std::endl;
    } else {
      std::cout << "fail5" << std::endl;
    }
    if (*our_return == *stl_return) {
      std::cout << "*pass5" << std::endl;
    } else {
      std::cout << "*fail5" << std::endl;
    }

    compare_lists(stl_list2, our_list2);
  }

  { // delete first element in 2 length list
    std::list<int> stl_list2{1, 2};
    cs19::LinkedList<int> our_list2{1, 2};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();

    auto stl_return = stl_list2.erase(stl_list2_start);
    auto our_return = our_list2.erase(our_list2_start);

    if (stl_return == stl_list2.begin()) {
      std::cout << "true6" << std::endl;
    } else {
      std::cout << "false6" << std::endl;
    }
    if (our_return == our_list2.begin()) {
      std::cout << "pass6" << std::endl;
    } else {
      std::cout << "fail6" << std::endl;
    }
    if (*our_return == *stl_return) {
      std::cout << "*pass6" << std::endl;
    } else {
      std::cout << "*fail6" << std::endl;
    }

    compare_lists(stl_list2, our_list2);
  }

  { // delete second element in 4 length list
    std::list<int> stl_list2{1, 2, 3, 4};
    cs19::LinkedList<int> our_list2{1, 2, 3, 4};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();
    std::advance(stl_list2_start, 1);
    std::advance(our_list2_start, 1);

    auto stl_return = stl_list2.erase(stl_list2_start);
    auto our_return = our_list2.erase(our_list2_start);

    auto stl_list2_check = stl_list2.begin();
    auto our_list2_check = our_list2.begin();
    std::advance(stl_list2_check, 1);
    std::advance(our_list2_check, 1);

    if (stl_return == stl_list2_check) {
      std::cout << "true7" << std::endl;
    } else {
      std::cout << "false7" << std::endl;
    }
    if (our_return == our_list2_check) {
      std::cout << "pass7" << std::endl;
    } else {
      std::cout << "fail7" << std::endl;
    }
    if (*our_return == *stl_return) {
      std::cout << "*pass7" << std::endl;
    } else {
      std::cout << "*fail7" << std::endl;
    }

    compare_lists(stl_list2, our_list2);
  }

  { // delete third element in 4 length list
    std::list<int> stl_list2{1, 2, 3, 4};
    cs19::LinkedList<int> our_list2{1, 2, 3, 4};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();
    std::advance(stl_list2_start, 2);
    std::advance(our_list2_start, 2);

    auto stl_return = stl_list2.erase(stl_list2_start);
    auto our_return = our_list2.erase(our_list2_start);

    auto stl_list2_check = stl_list2.begin();
    auto our_list2_check = our_list2.begin();
    std::advance(stl_list2_check, 2);
    std::advance(our_list2_check, 2);

    if (stl_return == stl_list2_check) {
      std::cout << "true8" << std::endl;
    } else {
      std::cout << "false8" << std::endl;
    }
    if (our_return == our_list2_check) {
      std::cout << "pass8" << std::endl;
    } else {
      std::cout << "fail8" << std::endl;
    }
    if (*our_return == *stl_return) {
      std::cout << "*pass8" << std::endl;
    } else {
      std::cout << "*fail8" << std::endl;
    }

    compare_lists(stl_list2, our_list2);
  }

  { // delete third element in 5 length list
    std::list<int> stl_list2{1, 2, 3, 4, 5};
    cs19::LinkedList<int> our_list2{1, 2, 3, 4, 5};

    auto stl_list2_start = stl_list2.begin();
    auto our_list2_start = our_list2.begin();
    std::advance(stl_list2_start, 2);
    std::advance(our_list2_start, 2);

    auto stl_return = stl_list2.erase(stl_list2_start);
    auto our_return = our_list2.erase(our_list2_start);

    auto stl_list2_check = stl_list2.begin();
    auto our_list2_check = our_list2.begin();
    std::advance(stl_list2_check, 2);
    std::advance(our_list2_check, 2);

    if (stl_return == stl_list2_check) {
      std::cout << "true9" << std::endl;
    } else {
      std::cout << "false9" << std::endl;
    }
    if (our_return == our_list2_check) {
      std::cout << "pass9" << std::endl;
    } else {
      std::cout << "fail9" << std::endl;
    }
    if (*our_return == *stl_return) {
      std::cout << "*pass9" << std::endl;
    } else {
      std::cout << "*fail9" << std::endl;
    }

    compare_lists(stl_list2, our_list2);
  }
}