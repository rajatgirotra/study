/*
 * C++17 defines a __has_include preprocessor expression which can check if your compiler can include a particular header if present.
 * it can be handy sometimes. like C++17 has a new header <charconv> which provides a set of fast operations of chars/string.
 * If that header is available, you would want to use it, otherwise you need to provide some alternate implementation.
 *
 * See below. its trivial.
 */

#if defined __has_include
  #if __has_include(<charconv>)
  #define has_charconv 1
  #include <charconv>
  #endif
#endif

#include <iostream>
#include <string>
#include <optional>
#include <cassert>
using namespace std;

std::optional<int> ConvertToInt(const string& str) {
    int value {};
#ifdef has_charconv
    const auto last = str.data() + str.size();
    const auto res = std::from_chars(str.data(), last, value);
    if(res.ec == std::errc{} && res.ptr == last)
        return value;
#else
    // alternate implementation
#endif
    return std::nullopt;
}

int main() {
    string s{"-925"};
    assert(ConvertToInt(s) == -925);
    return 0;
}