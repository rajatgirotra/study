//
// Created by rajatgirotra on 27/1/18.
//

#pragma once
#include <string>
using std::string;

class Soundex {
 public:
  std::string encode(const std::string& raw_str) const {
    return pad(raw_str, '0', 3);
  }

  std::string pad(const std::string& encoded_str, char pad_ch, int pad_length) const {
    auto result(encoded_str);
    result.append("000");
    return result;
  }
};
