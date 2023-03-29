/*
given a 32 bit integer  n, print its binary representation and the reverse of the binary representation
*/

#include <iostream>
#include <limits>
#include <cstdint>
#include <charconv>
#include <cstring>
#include <cassert>
#include <bitset>
using namespace std;

auto dec2bin(uint32_t value) {
    string binary{};
    do {
        auto digit = value % 2;
        binary.insert(0, 1, (digit == 0 ? '0' : '1'));
        value /= 2;
    } while(value != 0);
    return binary;
}


auto reverse_bits_of_integer(uint32_t value) {
    uint32_t result{0};
    while(value != 0) {
        auto digit = value % 2;
        result = (result << 1) | digit;
        value /= 2;
    }
    return dec2bin(result);
}

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Usage:\n\t" << argv[0] << " <Number> \n";
        return -1;
    }

    uint32_t number{};
    auto [ptr, ec] = std::from_chars(argv[1], argv[1]+strlen(argv[1]), number, 10);
    if(ec == std::errc{}) {
        cout << "binary of " << number << " is: " << dec2bin(number) << endl;
        cout << "revered binary is: " << reverse_bits_of_integer(number) << endl;
    } else {
       assert(false); // invalid input
    }
}
