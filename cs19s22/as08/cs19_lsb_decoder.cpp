/**
 * @file cs19_lsb_decoder.cpp
 *
 * You shall write a C++ program that replicates the behavior of cs19_image_steganography_decode, as follows:
 * The program shall expect one command-line argument denoting the number of channels/components in the image (e.g. 1 for grayscale, 3 for RGB, and 4 for RGBA).
 * The program shall read any number of bytes from standard input, assumed to be pixel values with one byte per pixel component (e.g. 3 bytes/24 bits per RGB pixel).
 * The least-significant bit of one byte in each pixel shall be considered one bit in a hidden/encoded message. The byte containing the special bit will cycle through the color components, e.g. in an RGB image: The red component of the first pixel, the green component of the second pixel, the blue component of the third pixel, the red component of the fourth pixel, etc.
 * The program shall assume the message is terminated with a null character (0b00000000).
 * The program shall print the entire decoded message (without the null character) to standard output.
 *
 * @author Karen Corscadden for CS 19, kmcorscadden@jeff.cis.cabrillo.edu
 */

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char **argv) {
  if (argc <= 1 || argc > 2) {
    return 1;
  }
  int argument = std::stoi(argv[1]);
  const int skip1[] = {0};
  const int skip3[] = {3, 3, 0};
  const int skip4[] = {4, 4, 4, 0};
  const int *skips;
  if (argument == 1) {
    skips = skip1;
  } else if (argument == 3) {
    skips = skip3;
  } else if (argument == 4) {
    skips = skip4;
  } else {
    return 1;
  }
  unsigned s = 0;
  std::vector<char> message;
  char temp = 0;
  unsigned i = 0;
  for (char byte; std::cin.read(&byte, 1);) {
    byte &= 1;
    temp <<= 1;
    temp |= byte;
    ++i;
    for (int j = skips[s]; j > 0; j--) {
      std::cin.read(&byte, 1);
    }
    if (skips[s] == 0) {
      s = 0;
    } else {
      s++;
    }
    if (i == 8) {
      message.push_back(temp);
      if (temp == 0) {
        break;
      }
      temp = 0;
      i = 0;
    }
  }
  std::cout << message.data();
}