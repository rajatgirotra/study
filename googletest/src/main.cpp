//
// Created by rajatgirotra on 28/4/18.
//
#include "soundex.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  algo::Soundex s;
  std::cout << s.encode("A") << std::endl;
}
