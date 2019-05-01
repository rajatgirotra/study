#include <iostream>
#include <string>
#include <cstring>

// anagrams are strings with same characters, in any order.
using namespace std;
namespace  {
    bool are_anagrams(const char* one, const char* two)  {
        if(strlen(one) != strlen(two))
            return false;
        int chars_count[256] {};
        int unique_chars {};
        int unique_found {};
        while(*one != 0) {
            if(chars_count[static_cast<int>(*one)] == 0)
                ++unique_chars;
            ++chars_count[static_cast<int>(*one)];
            ++one;
        }

        while(*two != 0) {
            if(chars_count[static_cast<int>(*two)] == 0)
                return false;
            --chars_count[static_cast<int>(*two)];
            if(chars_count[static_cast<int>(*two)] == 0) {
                ++unique_found;
                if(unique_found == unique_chars) {
                    return (*(two+1) == 0);
                }
            }
            ++two;
        }
        return false;
    }
}

int main() {
    cout << "anagrams(one, neo): " << std::boolalpha << are_anagrams("one", "neo") << endl;
    cout << "anagrams(abcdf, abcd): " << std::boolalpha << are_anagrams("abcdf", "abcd") << endl;
}