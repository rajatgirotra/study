/*
 * C++17 std::byte is very trivial. it is just an enum.
 * enum struct byte : unsigned char {};
 *
 * it allows you to safely work with byte and bit operations. To convert the byte to a number, just use std::to_integer()
 */

#include <cstddef>  // for std::byte
#include <iostream>
using namespace std;

int main() {
    constexpr std::byte b{1};
    //std::byte wrong {65535}; // error, narrowing conversion.

    constexpr auto b1 = b << 7;

    static_assert(std::to_integer<int>(b) == 0x01);
    static_assert(std::to_integer<int>(b1) == 0x80);

    constexpr std::byte c{255};
    constexpr auto c1 = b1 ^ c;
    static_assert(std::to_integer<int>(c) == 0xff);
    static_assert(std::to_integer<int>(c1) == 0x7f);
}
