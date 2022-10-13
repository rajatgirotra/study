// given two strings, write a method to decide if one is a permutation of the other.
// Example, donmra is a permutation of string "random"

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
using namespace std;

// with additional data structure
// mStr is main string, pStr is permute string
bool isPermutation(const std::string& mStr, const std::string& pStr) {
    // optimization. If lengths are unequal, return false
    if(mStr.size() != pStr.size()) {
        return false;
    }
    int count[256] {0};
    for(auto&& ch : mStr) {
        ++count[ch];
    }

    for(auto&& ch : pStr) {
        --count[ch];
        if(count[ch] < 0) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string s1 {"register"};
    std::string s2 {"grreetis"};
    cout << std::boolalpha << isPermutation(s1, s2) << endl;
}