//
// Created by rajatgirotra on 28/4/18.
//

#pragma once
#include <string>

namespace algo {
class Soundex {
 public:
     std::string encode(const std::string& raw_str);
};
}