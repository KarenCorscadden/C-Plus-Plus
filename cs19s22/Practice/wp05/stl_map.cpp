/**
 * @file stl_map.cpp
 *
 * Simple illustration of STL (unordered_)map.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */

#include <algorithm>  // std::replace
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::unordered_map<std::string, std::string> zip_codes;
  std::string city;
  {
    std::ifstream in_file("/srv/datasets/zip_tokens");
    for (std::string zip; in_file >> zip >> city;) {
      std::replace(city.begin(), city.end(), '_', ' ');  // STL algorithms are iterator-based!
      if (zip_codes.find(city) != zip_codes.end()) {
        zip_codes[city] += ' ' + zip;
      } else {
        zip_codes[city] = zip;
      }
    }
  }
  while (getline(std::cin, city))
    std::cout << zip_codes[city] << '\n';
}