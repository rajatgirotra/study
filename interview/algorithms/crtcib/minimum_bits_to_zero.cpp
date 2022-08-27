/*
Given an integer n, you must transform it into 0 using the following operations any number of times:

Change the rightmost (0th) bit in the binary representation of n. i.e. 0100101 --> 0100100

Change the ith bit in the binary representation of n if the (i-1)th bit is set to 1 and the (i-2)th through 0th bits are set to 0. i.e. 101100 --> 100100

Return the minimum number of operations to transform n into 0.

We can do this using dynamic programming. Lets try to be greedy by reducing the Most significant 1 to 0.
Example:

dfs(0110010) --> 
  1) look at bits[0] (most significant bit). 
      a) if it is 0, nothing to do and problem reduces to dfs(110010)
      b) if it is 1. then you need to make the rest of the bits 1 followed by one or more zeros. So if input is 110010, then we call helper(10010) + 1 (to change msb 1 to 0) + dfs(10000)
      c) base case is dfs(0) == 0, dfs(1) == 1.
      d) also we create a hashMap for memoization. i.e. if we compute dfs(x), we store it in the map and not re-compute it.

helper(0110010) -->
  2) look at bits[0] 
      base case:
      a) if it is 0, we have to make it 1. i.e we return 1 (meaning one operation)

 
  2.1) if bits[0] = 1, then we just need to change the rest of the bits to 0. i.e. we can use dfs() again
  2.2) if bits[0] = 0, then we need to change the rest of the bits to 1 followed by all zeros, so helper() + 1 + dfs(1000)
    
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

int dfs(const string&);

int helper(const string& bits) {
    static unordered_map<string, int> mem_helper{};

    // base case handling
    if(bits.size() == 1) {
        if(bits[0] == '0') {
            return 1;
        } else {
            return 0;
        }
    }

    if(mem_helper.find(bits) != mem_helper.end()) {
        return mem_helper[bits];
    }

    int ans = 0;
    // if bits[0] is '0', ignore it
    if(bits[0] == '0') {
        auto sz = bits.size();
        string dfs_arg{"1"};
        for(string::size_type i = 0; i < sz-2; ++i) {
            dfs_arg.insert(1, 1, '0');
        }
        ans = helper(bits.substr(1)) + 1 + dfs(dfs_arg);
    } else {
        auto sz = bits.size();
        ans = dfs(bits.substr(1));
    }

    mem_helper.emplace(bits, ans);
    return ans;
}

int dfs(const string& bits) {
    static unordered_map<string, int> mem_dfs{};

    // base case handling
    if(bits.size() == 1) {
        return static_cast<int>(bits[0]) - '0';
    }

    if(mem_dfs.find(bits) != mem_dfs.end()) {
        return mem_dfs[bits];
    }

    int ans = 0;
    // if bits[0] is '0', ignore it
    if(bits[0] == '0') {
        ans = dfs(bits.substr(1));
    } else {
        auto sz = bits.size();
        string dfs_arg{"1"};
        for(string::size_type i = 0; i < sz-2; ++i) {
            dfs_arg.insert(1, 1, '0');
        }
        ans = helper(bits.substr(1)) + 1 + dfs(dfs_arg);
    }

    mem_dfs.emplace(bits, ans);
    return ans;
}

int min_bits_to_zero(const string& bits) {
    return dfs(bits);
}

int main(int argc, char** argv) {
    assert(argc == 2);

    int64_t value{};

    auto [ptr, ec] {std::from_chars(argv[1], argv[1]+strlen(argv[1]), value)};
    if(ec == std::errc()) {
        // TODO: My logic
        auto bits = to_binary(value);
        cout << "Value: " << value << ", in binary: " << bits << ", minimum steps to zero: " << dfs(bits) << endl;
    } else if(ec == std::errc::invalid_argument) {
        cerr << "Input is not a number: " << argv[1] << endl;
    } else if(ec == std::errc::result_out_of_range) {
        cerr << "Input is not a number: " << argv[1] << endl;
    } 
}
