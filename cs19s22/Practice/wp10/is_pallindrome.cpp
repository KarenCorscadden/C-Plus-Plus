template <typename Iterator>
bool is_pallindrome(Iterator first, Iterator last) {
  --last;
  if (first == last) {
    return true;
  }
  if (*first == *last) {
    first++;
    last--
    return is_pallindrome(first, last);
  }
  return false;
}