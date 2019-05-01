/* for removing duplicates from a sorted string, we will not need additional space.
 * So space complexity should be O(1). Time complexity should be linear
 */

#include <iostream>
#include <string>
#include <cstring>
#include <ostream>
using namespace std;

namespace {
    void remove_duplicates_from_unsorted_string(char* const arg) {
        if(arg == nullptr) return;
        int len = strlen(arg);
        if(len < 2) return;
        bool has_char[256] {};
        int end = 1;
        has_char[static_cast<int>(arg[0])] = true;
        for(auto i = end; i < len; ++i) {
            if(!has_char[static_cast<int>(arg[i])]) {
                arg[end] = arg[i];
                ++end;
                has_char[static_cast<int>(arg[i])] = true;
            }
        }
        arg[end] = 0;
    }
}

int main() {
    char* null_string = nullptr;
    char empty_string[] {};
    char string_with_no_duplicates[] {"abcdef"};
    char string_with_duplicates[]  {"ababababaebgegfh"};
    char string_with_all_duplicates[]  {"zzzzzz"};

    remove_duplicates_from_unsorted_string(null_string);
    remove_duplicates_from_unsorted_string(empty_string);
    remove_duplicates_from_unsorted_string(string_with_no_duplicates);
    remove_duplicates_from_unsorted_string(string_with_duplicates);
    remove_duplicates_from_unsorted_string(string_with_all_duplicates);

    cout << "remove_duplicates_from_unsorted_string(null_string): " << (null_string == 0 ? "NULL_STRING" : "BUG") << endl;
    cout << "remove_duplicates_from_unsorted_string(empty_string): " << empty_string << endl;
    cout << "remove_duplicates_from_unsorted_string(string_with_no_duplicates): " << string_with_no_duplicates << endl;
    cout << "remove_duplicates_from_unsorted_string(string_with_duplicates): " << string_with_duplicates << endl;
    cout << "remove_duplicates_from_unsorted_string(string_with_all_duplicates): " << string_with_all_duplicates << endl;
}