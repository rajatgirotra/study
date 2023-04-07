/*
Given an integer n, you must transform it into 0 using the following operations any number of times:

Change the rightmost (0th) bit in the binary representation of n. i.e. 0100101 --> 0100100

Change the ith bit in the binary representation of n if the (i-1)th bit is set to 1 and the (i-2)th through 0th bits are set to 0. i.e. 101100 --> 100100

Return the minimum number of operations to transform n into 0.

Read this: https://cp-algorithms.com/algebra/gray-code.html. Generating gray code is super easy.

for i in 0..n:
   next_gray_code = i ^ (i >> 1)

basically here n is a gray code, and we have to reverse engineer to find i.

*/

#include <iostream>
#include <string>
#include <charconv>
#include <cassert>
#include <cstring>
#include <unordered_map>
using namespace std;

string to_binary(int64_t value) {
    string res{};
    res.reserve(64);
    do {
    //while(value != 0) {
        auto ch = value % 2;
        assert(ch == 0 || ch == 1);
        res.insert(0, 1, '0' + static_cast<char>(ch));
        value /= 2;
    } while(value != 0);
    return res;
}

int min_bits_to_zero(const string& bits) {
    int ans = 0;
    int last_bit = 0;
    int cur_bit;

    for(auto&& ch : bits) {
        cur_bit = (ch == '1' ?  last_bit ^ 1 : last_bit);
        ans = (ans << 1) + cur_bit;
        last_bit = cur_bit;
    }
    return ans;
}

int main(int argc, char** argv) {
    assert(argc == 2);

    int64_t value{};

    auto [ptr, ec] {std::from_chars(argv[1], argv[1]+strlen(argv[1]), value)};
    if(ec == std::errc()) {
        // TODO: My logic
        auto bits = to_binary(value);
        cout << "Value: " << value << ", in binary: " << bits << ", minimum steps to zero: " << min_bits_to_zero(bits) << endl;
    } else if(ec == std::errc::invalid_argument) {
        cerr << "Input is not a number: " << argv[1] << endl;
    } else if(ec == std::errc::result_out_of_range) {
        cerr << "Input is not a number: " << argv[1] << endl;
    } 
}
