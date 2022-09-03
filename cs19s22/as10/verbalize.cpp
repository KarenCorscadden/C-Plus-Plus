#include <gmpxx.h>
// #include "/opt/homebrew/include/gmpxx.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cassert>

/**
 * Verbalizes the given integer.
 *
 * @param value an integer, assumed to be nonnegative
 * @param number_names a mapping of orders of magnitude to their verbal equivalents
 * @param recurring whether this is a recursive call
 * @return the verbalized orders of magnitude of value, in descending order, e.g.
 *   verbalize(mpz_class(12345)) ==
 *     std::vector<string>{"twelve thousand", "three hundred forty-five"}
 */
std::vector<std::string> verbalize(const mpz_class &value,
                                   const std::map<mpz_class, std::string> &number_names,
                                   bool recurring = false);




int main(int argc, char **argv) {
  auto value = mpz_class(argv[1]);
  // read in  /srv/datasets/number_names.txt and create a map out of the data
  std::ifstream num_file("/srv/datasets/number_names.txt");
  mpz_class number;
  std::map<mpz_class, std::string> number_names;
  for (std::string name, snumber; num_file >> name >> snumber;) {
    number = mpz_class(snumber);
    number_names[number] = name;
  }
  auto verbalization = verbalize(value, number_names);
  while (!verbalization.empty()) {
    std::cout << verbalization.back() << std::endl;
    verbalization.pop_back();
  }
}

std::vector<std::string> verbalize(const mpz_class &value,
                                   const std::map<mpz_class, std::string> &number_names,
                                   bool recurring) {
  std::string to_return = "";
  if (value == 0 && recurring == false) {
    to_return = number_names.at(value);
    std::vector<std::string> returning;
    returning.push_back(to_return);
    return returning;
  }
  if (value < 1000) {
    if (value / 100 > 0) {
      to_return = number_names.at(value / 100) + " " + number_names.at(100);
    }
    mpz_class eval = value % 100;
    if (eval > 0) {
      try {
        number_names.at(eval);
        to_return += " " + number_names.at(eval);
      } catch (std::exception &e) {
        if (eval / 10 > 0) {
          if (to_return != "") {
            to_return += " ";
          }
          to_return += number_names.at((eval / 10) * 10);
        }
        eval = eval % 10;
        if (eval > 0) {
          to_return += "-" + number_names.at(eval);
        }
      }
    }
    std::vector<std::string> returning;
    if (value != 0 || recurring == false) {
      returning.push_back(to_return);
    }
    return returning;
  }
  // add recursive case here
  for (auto rev = number_names.rbegin(); rev != number_names.rend(); rev++) {
    // map key is rev->first
    if (value % (rev->first) == value) {
      continue;
    }
    mpz_class current = value / (rev->first);
    assert(current <= 1000);
    if (current == 0) {
      return verbalize(value % (rev->first), number_names, true);
    } else {
    // create the verbalization for the current order of magnitute.
    // return vector = current verb + verbalize(value % rev->first)
      if (current / 100 > 0) {
        to_return = number_names.at(current / 100) + " " + number_names.at(100);
      }
      current = current % 100;
      if (current > 0) {
        try {
          number_names.at(current);
          to_return += " " + number_names.at(current);
        } catch (std::exception &e) {
          if (current / 10 > 0) {
            if (to_return != "") {
              to_return += " ";
            }
            to_return += number_names.at((current / 10) * 10);
          }
          current = current % 10;
          if (current > 0) {
            to_return += "-" + number_names.at(current);
          }
        }
      }
      to_return = to_return + " " + rev->second;
      mpz_class verb_value = value % (rev->first);
      auto returning = verbalize(verb_value, number_names, true);
      returning.push_back(to_return);
      return returning;
    }
  }
  assert(false);
}