// Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures?
// string can contain any printable characters in ascii. (i.e. from ascii value 20 to 127)

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
using namespace std;

// with additional data structure
bool isUnique(const std::string& s) {
    bool occur[256] {false};
    for(auto&& ch : s) {
        if(occur[ch]) {
            return false;
        }
        occur[ch] = true;
    }
    return true;
}

// without additional data structure
bool isUnique2(const std::string& s) {
    for(int i = 1; i < s.size(); ++i) {
        for(int j = i-1; j>=0; --j) {
            if(s[i] == s[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::string str {"abcdefghi"};
    cout << std::boolalpha << isUnique2(str) << endl;
}