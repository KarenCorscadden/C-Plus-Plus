#include "cs19_counting_sort.h"

namespace cs19 {
  void counting_sort(int *array, unsigned array_len) {
    if (array_len < 1) {
      return;
    }
    int max = array[0];
    int min = array[0];
    for (unsigned i = 1; i < array_len; ++i) {
      if (array[i] > max) {
        max = array[i];
      }
      if (array[i] < min) {
        min = array[i];
      }
    }
    unsigned tally_len = max - min + 1;
    int *tally_array = new int[tally_len];
    for (unsigned i = 0; i < tally_len; ++i) {
      tally_array[i] = 0;
    }
    for (unsigned i = 0; i < array_len; ++i) {
      ++tally_array[array[i] - min];
    }
    unsigned j = 0;
    for (unsigned i = 0; i < tally_len; ++i) {
      // iterate through tally_array and add values to array
      while (tally_array[i] > 0 && j < array_len) {
        array[j] = i + min;
        ++j;
        --tally_array[i];
      }
    }
    delete[] tally_array;
  }
}  // namespace cs19