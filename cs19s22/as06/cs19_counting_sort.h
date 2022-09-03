/**
 * @file cs19_counting_sort.h
 *
 * This is your chance to write one of the simplest but more interesting sort algorithms.
 *
 * @author A student in CS 19 at Cabrillo College, someone@jeff.cis.cabrillo.edu
 */
#ifndef CS19_COUNTING_SORT_H_
#define CS19_COUNTING_SORT_H_

namespace cs19 {

/**
 * Uses the counting-sort algorithm to sort an array of integers.
 *
 * @param array the array to sort
 * @param array_len the length of the array
 */
void counting_sort(int *array, unsigned array_len);

}  // namespace cs19

#endif