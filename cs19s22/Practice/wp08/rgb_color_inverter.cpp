/**
 * @file rgb_color_inverter.cpp
 *
 * Treating bytes as if they represent components of RGB pixels. Here we modify a RGB "image"
 * on stdin, inverting the color components in each pixel to create a "negative" image.
 * We output raw binary data, suitable for input to a program like ImageMagick's "convert" utility:
 * convert img_file rgb:- | ./a.out | convert -depth 8 -size widthxheight rgb:- out.jpg
 *
 * @author Jeffrey Bergamini for CS 19, jbergamini@jeff.cis.cabrillo.edu
 */

#include <iostream>

int main() {
  // This is going to be slow if we read/write one byte at a time, but so be it for now.
  for (char byte; std::cin.read(&byte, 1);) {
    char trash[2];
    byte = static_cast<char>(static_cast<uint8_t>(byte));
    std::cout.write(&byte, 1);
    std::cin.read(trash, 2);
  }
}