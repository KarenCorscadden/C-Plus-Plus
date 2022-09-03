/**
 * @file cs19_rna.h
 *
 * Modeling a RNA sequence.
 *
 * @author Karen Corscadden for CS 19, kmcorscadden@jeff.cis.cabrillo.edu
 */

#ifndef _CS19_RNA_H
#define _CS19_RNA_H

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>

namespace cs19 {

/**
 * Class Rna models a mutable RNA sequence, with operators providing an idiomatic C++ interface.
 *
 * Since this is not a class template, we would normally separate interface from implementation, but
 * I have kept it all in the header file here to make discussion of this class a bit easier.
 */
class Rna {
 public:
  /**
   * Default constructor (created automatically in the absence of other constructors).
   * Creates an empty RNA sequence.
   */
  Rna() {
    // Nothing to do here. this->sequence is already initialized as an empty string.
  }

  /**
   * Template sequence contructor: Works with any iterable sequence of legal RNA characters.
   * @tparam Sequence iterable type containing A/C/G/T characters, e.g. std::string/std::list<char>
   * @throws std::domain_error for any sequence containing invalid RNA characters.
   */
  template <typename Sequence>
  Rna(const Sequence &contents) {
    this->operator+=(contents);  // reuse compound assignment/addition function
  }

  /**
   * Initializer-list constructor for a list of legal RNA characters.
   * e.g. cs19::Rna{'G', 'A', 'T', 'T', 'A', 'C', 'A'}
   * @throws std::domain_error if any element in the list is an invalid RNA nucleotide character.
   */
  Rna(std::initializer_list<char> list) {
    for (char nucleotide : list) {
      this->operator+=(nucleotide);  // delegate to compound assignment/addition function
    }
  }

  // // Copy constructor (not necessary—compiler will make this automatically!)
  // Rna(const Rna &that) {
  //   this->operator=(that);
  // }

  // // Copy assignment (not necessary—compiler will make this automatically!)
  // Rna &operator=(const Rna &that) {
  //   this->sequence = that.sequence;
  //   return *this;
  // }

  /**
   * Copy assignment from string.
   * @tparam Sequence iterable type containing A/C/G/T characters, e.g. std::string/std::list<char>
   * @throws std::domain_error for any sequence containing invalid RNA characters.
   */
  template <typename Sequence>
  Rna &operator=(const Sequence &other) {
    this->sequence.clear();
    this->operator+=(other);  // delegate to compound assignment/addition function
    return *this;             // assignment statements must evaluate to their targets
  }

  /**
   * Addition implies concatenation.
   * @tparam Sequence iterable type containing A/C/G/T characters, e.g. std::string/std::list<char>
   * @throws std::domain_error for any sequence containing invalid RNA characters.
   */
  template <typename Sequence>
  Rna operator+(const Sequence &that) const {
    return Rna(this->sequence + std::string(that.begin(), that.end()));
  }

  /**
   * Compound addition/assignment: Return this sequence concatenated with another.
   */
  Rna operator+(const Rna &that) const {
    return Rna(this->sequence + that.sequence);
  }

  /**
   * Compound addition/assignment.
   * Appends another iterable sequence containing A/C/G/T chars to this sequence.
   * @tparam Sequence iterable type containing A/C/G/T characters, e.g. std::string/std::list<char>
   * @throws std::domain_error for any sequence containing invalid RNA characters.
   */
  template <typename Sequence>
  Rna &operator+=(const Sequence &appendage) {
    for (char nucleotide : appendage)
      this->operator+=(nucleotide);  // delegate to compound assignment/addition(char) function
    return *this;
  }

  /**
   * Compound addition/assignment: Appends another Rna object's sequence to this sequence.
   */
  Rna &operator+=(const Rna &appendage) {
    this->sequence += appendage.sequence;
    return *this;
  }

  /**
   * Compound addition/assignment: Appends another Rna object's sequence to this sequence.
   */
  Rna &operator+=(const char *appendage) {
    this->operator+=(std::string(appendage));  // delegate to the (std::string) overloaded version
    return *this;
  }

  /**
   * Compound addition/assignment. Appends one nucleotide character (A/C/G/T) to this sequence.
   * @throws std::domain_error if nucleotide is an invalid RNA nucleotide character.
   */
  Rna &operator+=(char nucleotide) {
    // Make sure no illegal characters can be added to a RNA sequence:
    if (this->complements.find(nucleotide) == this->complements.end())
      throw std::domain_error(std::string("Invalid character for RNA sequence: ") + nucleotide);
    this->sequence += nucleotide;
    return *this;
  }

  /**
   * Compound multiplication/assignment: Repeats/concatenates this sequence a number of times.
   */
  Rna &operator*=(std::size_t repeat_count) {
    std::string new_sequence;
    for (std::size_t i = 0; i < repeat_count; ++i)
      new_sequence += this->sequence;
    this->sequence = new_sequence;
    return *this;
  }

  /**
   * const subscript (used when a Rna object is an rvalue, i.e. not the target of an assignment).
   * e.g. cs19::Rna(std::string("GATTACA"))[2] == 'T'
   */
  const char operator[](std::size_t index) const {
    return this->sequence[index];
  }

  // non-const subscript (used when a Rna object is an lvalue, i.e. the target of an assignment)
  // We probably don't want to allow this! It would allow introducing non-Rna characters, e.g.:
  //   some_Rna_object[100] = '!';
  // Maybe we should instead offer this through a named member function instead (see "set").
  // char &operator[](std::size_t index) {
  //   return this->sequence[index];
  // }

  /**
   * Complement operator: Returns this sequence's complementary sequence.
   * e.g. ~cs19::Rna("GATTACA") == cs19::Rna("CTAATGT")
   */
  Rna operator~() const {
    Rna complement(*this);
    for (char &nucleotide : complement.sequence)
      nucleotide = this->complements.at(nucleotide);
    return complement;
  }

  /**
   * Unary minus operator: Returns this sequence in reverse.
   * e.g. -cs19::Rna("GATTACA") == cs19::Rna("ACATTAG")
   */
  Rna operator-() const {
    return Rna(std::string(this->sequence.rbegin(), this->sequence.rend()));
  }

  /**
   * Binary XOR operator (^) implies Hamming distance (Rosalind Problem HAMM).
   * e.g. cs19::Rna("GATTACA") ^ cs19::Rna("CATTACA") == 1
   */
  int operator^(const Rna &that) const {
    if (this->sequence.size() != that.sequence.size())
      return -1;
    int distance = 0;
    for (int i = 0; i < this->sequence.size(); ++i)
      if (this->sequence[i] != that.sequence[i])
        ++distance;
    return distance;
  }

  /**
   * Multiplication operator: Returns this sequence repeated/concatenated a number of times.
   * e.g. cs19::Rna("GATTACA") * 2 == cs19::Rna("GATTACAGATTACA")
   */
  Rna operator*(int repeat_count) const {
    std::string new_sequence;
    for (int i = 0; i < repeat_count; ++i)
      new_sequence += this->sequence;
    return Rna(new_sequence);
  }

  // Two Rna objects compare equal if they contain the same sequence of nucleotides.
  bool operator==(const Rna &that) const {
    return this->sequence == that.sequence;
  }
  bool operator!=(const Rna &that) const {
    return this->sequence != that.sequence;
  }

  /**
   * Determines whether this RNA contains the same values as another iterable sequence.
   * @tparam Sequence iterable type containing A/C/G/T characters, e.g. std::string/std::list<char>
   */
  template <typename Sequence>
  bool operator==(const Sequence &that) const {
    return std::equal(this->sequence.begin(), this->sequence.end(), that.begin(), that.end());
  }
  template <typename Sequence>
  bool operator!=(const Sequence &that) const {
    return !std::equal(this->sequence.begin(), this->sequence.end(), that.begin(), that.end());
  }

  // Two Rna objects compare equal if they contain the same sequence of nucleotides.
  bool operator==(const char *that) const {
    return this->sequence == that;
  }
  bool operator!=(const char *that) const {
    return this->sequence != that;
  }

  // A Rna sequence is Boolean "true" if non-empty.
  operator bool() const {
    return !this->sequence.empty();
  }

  /**
   * Stream insertion operator: object will appear as a plain string sequence, e.g. "GATTACA"
   * "friend": Makes this a global function instead of a member function, but the global function
   * has access to private/protected members of class. This function will be used whenever an object
   * of type cs19::Rna is inserted into an object of type std::ostream (e.g. std::cout).
   */
  friend std::ostream &operator<<(std::ostream &out, const Rna &rna) {
    out << rna.sequence;
    return out;
  }

  /**
   * Stream extraction operator:
   * Support extracting from a istream into a Rna using same rules as std::string.
   */
  friend std::istream &operator>>(std::istream &in, Rna &rna) {
    std::string sequence;
    in >> sequence;
    rna = sequence;
    return in;
  }

  /**
   * Convenience function for when we explicitly want a string version of the sequence.
   * cs19::Rna("GATTACA").to_string() == "GATTACA"
   */
  std::string to_string() const {
    return this->sequence;  // Will return a *copy* of our private, encapsulated string object
  }

  // Returns the length of this sequence.
  std::size_t size() const {
    return this->sequence.size();
  }

  // pop_back() akin to STL sequence containers
  void pop_back() {
    this->sequence.pop_back();
  }

  // back() akin to STL sequence containers
  char back() const {
    return this->sequence.back();
  }

  void set(std::size_t pos, char nucleotide) {
    if (this->complements.find(nucleotide) == this->complements.end())
      throw std::domain_error(std::string("Invalid character for RNA sequence: ") + nucleotide);
    this->sequence[pos] = nucleotide;
  }

  Rna subsequence(std::size_t pos, std::size_t count) const {
    return Rna(this->sequence.substr(pos, count));
  }

  // Rosalind Problem GC
  double gc_content() const {
    int gc_count = 0;
    for (char nucleotide : this->sequence)
      if (nucleotide == 'G' || nucleotide == 'C')
        ++gc_count;
    return static_cast<double>(gc_count) / this->sequence.size();
  }

  // Rosalind Problem DNA
  std::map<char, int> nucleotide_counts() const {
    std::map<char, int> counts;
    for (char nucleotide : this->sequence)
      ++counts[nucleotide];  // std::map::operator[] auto-initializes value to 0
    return counts;
  }

  // count a single nucleotide
  std::size_t count(char nucleotide) {
    std::size_t ret = 0;
    for (char c : this->sequence)
      if (c == nucleotide)
        ++ret;
    return ret;
  }

 private:
  std::string sequence;
  std::map<char, char> complements{{'A', 'U'}, {'U', 'A'}, {'C', 'G'}, {'G', 'C'}};
};

}  // namespace cs19

#endif  // _CS19_RNA_H