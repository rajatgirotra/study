//
// Created by rajatgirotra on 28/4/18.
//
#include "soundex.hpp"
#include <string>
#include <gmock/gmock.h>

using namespace algo;

TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
  Soundex soundex;
  ASSERT_EQ(soundex.encode("A"), std::string("A"));
}
