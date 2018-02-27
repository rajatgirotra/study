//
// Created by rajatgirotra on 27/1/18.
//

#include "Soundex.hpp"
#include "gmock/gmock.h"
#include <cstdlib>
#include <ctime>
#include <string>

using ::testing::Eq;


class SoundexEncoding : public ::testing::Test {
 public:
  Soundex soundex;
  static const std::string one_letter_strings[];
};

const std::string SoundexEncoding::one_letter_strings[] = {"A", "B", "C", "D", "E", "F"};

TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord) {
  srand(time(0));
  int i = rand() % sizeof(SoundexEncoding::one_letter_strings)/sizeof(SoundexEncoding::one_letter_strings[0]);
  auto encoded = soundex.encode(SoundexEncoding::one_letter_strings[i]);
  auto result = std::string(SoundexEncoding::one_letter_strings[i]).append("000");
  ASSERT_THAT(encoded, Eq(result));
}

TEST_F(SoundexEncoding, PadWithZerosToEnsureThreeDigits) {
  srand(time(0));
  int i = rand() % sizeof(SoundexEncoding::one_letter_strings)/sizeof(SoundexEncoding::one_letter_strings[0]);
  auto encoded = soundex.encode(SoundexEncoding::one_letter_strings[i]);
  auto result = std::string(SoundexEncoding::one_letter_strings[i]).append("000");
  ASSERT_THAT(encoded, Eq(result));
}