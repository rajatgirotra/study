/*
 * std::string_view
 */
#include <string_view>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    // many ways to create string_view.

    // 1. from const char*,
    // the character array underlying string_view will be null-terminated. So std::strlen() will give correct result
    string_view s1 = "Hello";
    cout << "string_view from const char*: " << s1 << ", length: " << s1.size() << ", std::strlen(): " << std::strlen(s1.data()) << endl;

    // 2. from const char* with length (basically constructing with a slice)
    // the character array underlying string_view will NOT be null-terminated
    // so std::strlen() will be garbage.
    const char* p = "HelloWorld";
    string_view s2(p, 6);
    cout << "string_view from const char* and length: " << s2 << ", length: " << s2.size() << ", std::strlen(): " << std::strlen(s2.data()) << endl;

    // 3. from std::string
    std::string word = "Hello\0 Cruel World";
    string_view s3(word);
    cout << "string_view from std::string " << s3 << ", length: " << s3.size() << ", std::strlen(): " << std::strlen(s3.data()) << endl;
    cout << "string_view from std::string " << s3.data() << endl;

    // 4. from sv literal
    // also when the character sequence has an embedded null, std::strlen() will be incorrect.
    string_view s4 = "Hello\0 Cruel World"sv;
    cout << "string_view from sv literal " << s4 << ", length: " << s4.size() << ", std::strlen(): " << std::strlen(s4.data()) << endl;
    cout << "string_view from sv literal " << s4.data() << endl; // data returns const char* so output stops after printing "Hello"

    // 5. from char array
    // error: the underlying character array is not null-terminated
    char array[3] = {'B', 'a', 'r'};
    std::string_view s5(array, sizeof array);
    cout << "string_view from character array " << s5 << ", length: " << s5.size() << ", std::strlen(): " << std::strlen(s5.data()) << endl;

    // How do you create a std::string from a string_view?
    std::string tempStr { s4.data(), s4.size() }; // like this
    cout << "string constructed from string_view: " << tempStr << endl;
}

/*
 * As string_view may not contain \0 at the end of the string. It is problematic with all functions that accept traditional C-strings
 * because string_view breaks with C-string termination assumptions. If a function accepts only a const char* parameter,
 * it’s probably a bad idea to pass string_view into it. On the other hand, it might be safe when such a function accepts
 * const char* and length parameters. Functions like atoi(), atof() aren't compatible with string_view
 *
 * In general, the lifetime of a string_view must never exceed the lifetime of the string-owning object.
 */
