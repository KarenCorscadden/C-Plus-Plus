// Double quotes after #include implies a file path relative to this file.
// The following will if work cs19_c_strings.h is in the same directory as this file.
#include "cs19_c_strings.h"
#include <cassert>
#include <stdio.h>

int main() {
  char msg[] = "12345";
  printf ("%d \n", cs19::atoi(msg));
  assert(cs19::strlen(msg) == 5);
  assert(cs19::atoi(msg) == 12345);
  assert(cs19::strpbrk(msg, "abc543") == msg + 2);

  char s1[] = "hello";
  char s2[] = "123";
  char s3[100];
  cs19::strzip(s1, s2, s3);
  printf ("%s \n", s3);
  assert(cs19::strlen(s1) == 5);
  assert(cs19::strlen(s2) == 3);
  assert(cs19::strlen(s3) == 8);
  assert(!cs19::strcmp(s3, "h1e2l3lo"));

  assert(cs19::strchr("h1e2l3lo", 'z') == nullptr);
  assert(cs19::strchr(s3, 'e') == &s3[2]);

  assert(cs19::strcmp("Apple", "Banana") < 0);
  assert(cs19::strcmp("wat", "wat") == 0);
  assert(cs19::strcmp("apple", "Banana") > 0);

  assert(cs19::strrchr(s3, 'l') == &s3[6]);

  assert(cs19::strstr(s3, "2l3") == &s3[3]);
  assert(cs19::strstr(s3, "123") == nullptr);
  assert(cs19::strstr(s3, "23l") == nullptr);
  assert(cs19::strstr(s3, "lo") == &s3[6]);
  assert(cs19::strstr(s3, "o") == &s3[7]);
  assert(cs19::strstr(s3, "h1e2l3lo") == &s3[0]);
  assert(cs19::strstr(s3, "h") == &s3[0]);
  assert(cs19::strstr(s3, "l") == &s3[4]);
  assert(cs19::strstr(s3, "h1e2l3lo1") == nullptr);
  assert(cs19::strstr(s3, "") == nullptr);

  char s4[] = "Hello";
  char s5[] = "Uryyb";
  char s6[] = "Hello";
  cs19::str_rot13(s4);
  assert(*s4 == *s5);
  cs19::str_rot13(s4);
  assert(*s4 == *s6);

  cs19::strrev(s1);
  printf("%s \n", s1);
  assert(cs19::strcmp(s1, "olleh") == 0);
  cs19::strrev(s3);
  printf("%s \n", s3);
  assert(cs19::strcmp(s3, "ol3l2e1h") == 0);

  printf("sucess! \n");
}