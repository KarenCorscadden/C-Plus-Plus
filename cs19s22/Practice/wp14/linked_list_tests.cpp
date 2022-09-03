#include "cs19_linked_list_smart_pointers.h"
int main(){
  cs19::LinkedList<char> list;
  list.reverse();
  std::cout << list << '\n';
  for (auto c : std::string("Hello"))
    list.push_back(c);
  std::cout << list << '\n';
  cs19::LinkedList<char> copy = list;
  std::cout << "copied" << std::endl;
  copy.resize(10, '!');
  std::cout << copy << std::endl;
  list.remove('o');
  std::cout << copy << std::endl;
  copy.unique();
  std::cout << copy << std::endl;
  std::cout << list << '\n' << copy << '\n';
  list.remove('l');
  copy.remove('H');
  list.remove('k');
  list.reverse();
  std::cout << list << std::endl;
  list.resize(1);
  std::cout << list << std::endl;
  list.reverse();
  std::cout << list << std::endl;
  copy.reverse();
  std::cout << copy << std::endl;
}