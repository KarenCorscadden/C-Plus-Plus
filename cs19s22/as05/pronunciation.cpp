/**
 * @file pronunciation.cpp
 *
 * English Word to IPA pronunciation translator.
 *
 * @author Karen Corscadden for CS 19, kmcorscadden@jeff.cis.cabrillo.edu
 */

#include <algorithm>  // std::replace
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>  // istringstream
#include <set>

int main(int argc, char **argv) {
  std::unordered_map<std::string, std::string> IPAmap;
  std::unordered_map<std::string, std::vector<std::string> > ARPAbet;
  std::string words, line;
  {
    std::ifstream in_file("/srv/datasets/arpabet-to-ipa");
    for (std::string ARPA, IPA; in_file >> ARPA >> IPA;) {
      if (IPAmap.find(ARPA) != IPAmap.end()) {
        IPAmap[ARPA] += ' ' + IPA;
      } else {
        IPAmap[ARPA] = IPA;
      }
    }
  }
  {
    std::ifstream in_file("/srv/datasets/cmudict-0.7b-words");
    while (getline(in_file, line)) {
      std::string word;
      std::istringstream iss(line);
      std::vector<std::string> sylls;
      iss >> word;
      for (std::string syll; iss; iss >> syll) {
        sylls.push_back(syll);
      }
      if (ARPAbet.find(word) != ARPAbet.end()) {
        ARPAbet[word].insert(ARPAbet[word].end(), sylls.begin(), sylls.end());
      } else {
        ARPAbet[word] = sylls;
      }
    }
  }
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      std::string word = argv[i];
      std::transform(word.begin(), word.end(), word.begin(), toupper);
      std::string pronunciation;
      std::set<std::string> pronunciations;
      if (ARPAbet.find(word) != ARPAbet.end()) {
        for (std::string syll : ARPAbet[word]) {
            pronunciation += IPAmap[syll];
        }
        pronunciations.insert(pronunciation);
        pronunciation = "";
        int n = 1;
        std::string temp = word + '(' + std::to_string(n) + ')';
        while (ARPAbet.find(temp) != ARPAbet.end()) {
          for (std::string syll : ARPAbet[temp]) {
            pronunciation += IPAmap[syll];
          }
          pronunciations.insert(pronunciation);
          pronunciation = "";
          ++n;
          temp = word + '(' + std::to_string(n) + ')';
        }
      }
      for (std::string pro : pronunciations) {
        std::cout << pro << std::endl;
      }
    }
  } else {
    while (getline(std::cin, words)) {
      std::istringstream iss(words);
      for (std::string word; iss; iss >> word) {
        std::transform(word.begin(), word.end(), word.begin(), toupper);
        std::string pronunciation;
        std::set<std::string> pronunciations;
        if (ARPAbet.find(word) != ARPAbet.end()) {
          for (std::string syll : ARPAbet[word]) {
            pronunciation += IPAmap[syll];
          }
          pronunciations.insert(pronunciation);
          pronunciation = "";
          int n = 1;
          std::string temp = word + '(' + std::to_string(n) + ')';
          while (ARPAbet.find(temp) != ARPAbet.end()) {
            for (std::string syll : ARPAbet[temp]) {
              pronunciation += IPAmap[syll];
            }
            pronunciations.insert(pronunciation);
            pronunciation = "";
            ++n;
            temp = word + '(' + std::to_string(n) + ')';
          }
        }
        for (std::string pro : pronunciations) {
          std::cout << pro << std::endl;
        }
      }
    }
  }
}