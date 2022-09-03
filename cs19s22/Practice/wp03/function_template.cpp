#include <iostream>
#include <chrono>
#include <ctime>

template <typename Printable>
void week03_log(Printable input) {
  auto time = std::chrono::system_clock::now();
  std::time_t log_time = std::chrono::system_clock::to_time_t(time);
  printf("%.24s: ", std::ctime(&log_time));
  std::cout << input << std::endl;
}

int main() {
  week03_log(10);          // Output: (Current date/time): 10
  week03_log("whatever");  // Output: (Current date/time): whatever
  week03_log(1.12345);     // Output: (Current date/time): 1.2345
}