/*
 * std::string_view is just a NON-OWNING VIEW of a sequence of characters.
 * Under the hood it is implemented as a pointer to a start of a sequence and the length of the sequence.
 * std::string_view can save you from creating a number of temporary string objects in your code and give you good
 * optimization benefits. The only thing to remember with std::string_view is that if the underlying character sequence
 * is gone, your string_view object also becomes rubbish.
 *
 * REMEMBER THAT A string_view may not always be null terminated.
 */

#include <string_view>
#include <string>
#include <iostream>
using namespace std;

std::string FindBeginning(const string& word, const string& pattern) {
    return word.substr(word.find(pattern));
}

std::string_view FindBeginning(string_view word, string_view pattern) {
    return word.substr(word.find(pattern));
}

int main() {
    /* How many copies of string are created */
    std::string str {"This is a happy world"};
    auto substr = FindBeginning(str, "happy world");
    cout << substr << endl;

    std::string str2 {"This is a happy world"};
    auto substr2 = FindBeginning(str2, "happy world");
    cout << substr2 << endl;

}

/*
 * Answer is minimum 3.
 * 1. the str object itself.
 * 2. the "happy world" argument is a const char* which is converted to std::string as second argument pattern is a string
 * 3. the return value is std::string
 *
 * More copies may be created if compiler doesn't do copy elision. but with string_view version, zero copies of std::string
 * are created. std::string_view also provides substr() function.
 */
