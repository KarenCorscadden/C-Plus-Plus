#include "cs19_c_strings.h"

namespace cs19 {

unsigned atoi(const char *str) {
  std::size_t length = strlen(str);
  unsigned value = 0;
  unsigned temp = 0;
  for (std::size_t i = 0; i < length; ++i) {
    temp = static_cast<unsigned>(str[i] - '0');
    value *= 10;
    value += temp;
  }
  return value;
}

const char *strchr(const char *haystack, const char needle) {
  std::size_t length = strlen(haystack);
  for (std::size_t i = 0; i < length; ++i) {
    if (haystack[i] == needle) {
      return &haystack[i];
    }
  }
  return nullptr;
}

int strcmp(const char *str1, const char *str2) {
  std::size_t len1 = strlen(str1);
  std::size_t len2 = strlen(str2);
  std::size_t length = 0;
  if (len1 < len2) {
    length = len1;
  } else {
    length = len2;
  }
  for (std::size_t i = 0; i < length; ++i) {
    if (str1[i] < str2[i]) {
      return -1;
    } else if (str1[i] > str2[i]) {
      return 1;
    }
  }
  if (len1 == len2) {
    return 0;
  } else if (len1 < len2) {
    return -1;
  } else {
    return 1;
  }
}

std::size_t strlen(const char *str) {
  std::size_t length = 0;
  for (; *str; ++str) {
    ++length;
  }
  return length;
}

const char *strpbrk(const char *haystack, const char *char_list) {
  const char *strloc = nullptr;
  std::size_t length = strlen(char_list);
  const char *strtemp = nullptr;
  for (std::size_t i = 0; i < length; ++i) {
    strtemp = strchr(haystack, char_list[i]);
    if (strloc == nullptr) {
      strloc = strtemp;
    } else if (strtemp != nullptr && strtemp < strloc) {
      strloc = strtemp;
    }
  }
  return strloc;
}

const char *strrchr(const char *haystack, const char needle) {
  std::size_t length = strlen(haystack);
  const char *nedloc = nullptr;
  for (std::size_t i = 0; i < length; ++i) {
    if (haystack[i] == needle) {
      nedloc = &haystack[i];
    }
  }
  return nedloc;
}

char *strrev(char *str) {
  std::size_t length = strlen(str);
  std::size_t left = 0;
  if (length == 0) {
    return str;
  }
  std::size_t right = length - 1;
  while (left < right) {
    char temp = str[left];
    str[left] = str[right];
    str[right] = temp;
    ++left;
    --right;
  }
  return str;
}

const char *strstr(const char *haystack, const char *needle) {
  std::size_t haylength = strlen(haystack);
  std::size_t nedlength = strlen(needle);
  const char *location = nullptr;
  bool match = false;
  if (nedlength > haylength) {
    return location;
  }
  if (nedlength == 0 || haylength == 0) {
    return location;
  }
  for (std::size_t i = 0; i < haylength - (nedlength - 1); ++i) {
    if (haystack[i] == needle[0]) {
      match = true;
      for (std::size_t j = 1; j < nedlength; ++j) {
        if (haystack[i + j] != needle[j]) {
          match = false;
          break;
        }
      }
      if (match == true) {
        location = &haystack[i];
        return location;
      }
    }
  }
  return location;
}

void strzip(const char *str1, const char *str2, char *output) {
  std::size_t length1 = strlen(str1);
  std::size_t length2 = strlen(str2);
  std::size_t i = 0;
  std::size_t j = 0;
  std::size_t k = 0;
  while (i < length1 || j < length2) {
    if (i < length1) {
      output[k] = str1[i];
      ++k;
      ++i;
    }
    if (j < length2) {
      output[k] = str2[j];
      ++k;
      ++j;
    }
  }
  output[k] = '\0';
}

char *str_rot13(char *str) {
  std::size_t length = strlen(str);
  for (std::size_t i = 0; i < length; ++i) {
    if ((str[i] >= 'A' && str[i] <= 'M') || (str[i] >= 'a' && str[i] <= 'm')) {
      str[i] += 13;
    } else if ((str[i] >= 'N' && str[i] <= 'Z') || (str[i] >= 'n' && str[i] <= 'z')) {
      str[i] -= 13;
    }
  }
  return str;
}

}  // namespace cs19