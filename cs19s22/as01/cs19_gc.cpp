// CS19s22 Assignment 01
// Solution to modified Rosalind GC problem
// Read 1 DNA string from standard input (std::cin)
// Print GC percentage to 3 decimal places to standard output (std::cout)

#include <iostream>
#include <string>

int main() {
  int gc_count = 0, total_count = 0;
  double gc_percent = 0;

  // Iterate over standard input one line at a time
  for (std::string line; std::getline(std::cin, line);) {
  // Iterate over each dna line incrementing gc_count and total_count appropriately
    for (char base : line) {
      if (base == 'G' || base == 'C') {
        gc_count++;
        total_count++;
      } else if (base == 'A' || base == 'T') {
        total_count++;
      }
    }
  }

  // Calculate GC Percent then print to standard output
  if (total_count != 0) {
    gc_percent = static_cast<double>(gc_count) / total_count * 100;
  }
  std::cout << gc_percent << '\n';
}