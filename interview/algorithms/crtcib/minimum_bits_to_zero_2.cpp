/*
using Gray codes
*/

#include <iostream>
#include <string>
#include <charconv>
#include <cassert>
#include <cstring>
using namespace std;

uint64_t min_bits_to_zero(uint64_t value) {
   uint64_t i{};
   for (i = 0; i < (1UL<<63); ++i) {
        auto x = (i ^ (i >> 1));
        if (x == value)
            break;
   }
   return i;
}

int main(int argc, char** argv) {
    assert(argc == 2);

    int64_t value{};

    auto [ptr, ec] {std::from_chars(argv[1], argv[1]+strlen(argv[1]), value)};
    if(ec == std::errc()) {
        cout << "Value: " << value << ", minimum steps to zero: " << min_bits_to_zero(value) << endl;
    } else if(ec == std::errc::invalid_argument) {
        cerr << "Input is not a number: " << argv[1] << endl;
    } else if(ec == std::errc::result_out_of_range) {
        cerr << "Input is not a number: " << argv[1] << endl;
    } 
}
