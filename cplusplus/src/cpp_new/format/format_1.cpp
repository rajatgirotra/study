/*
 * the std::format() library had a goal of being at least as fast as std::sprintf() or even faster.
 * currently sprintf() is faster than using std string streams of std::to_string(), but now std::format() is preferred.
 *
 * Very trivial and flexible way to format. Let's look at some examples:
 * in std::format, you give a compile time format string (i.e. a string literal, a constexpr string or string_view).
 * passing a compile time string is what actually makes std::format() beat sprintf() performance.
 *
 * It yields an std::string, for which memory is allocated on the fly (this can be a performance issue), so std::format_to_n()
 * is also available. We will shortly look at it.
 *
 * the format string can have zero or more curly braces, which are format specifiers. After the format string, you can pass n arguments.
 * the values of the n arguments are used in the format specifiers.
 */

#include <iostream>
#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <chrono>
using namespace std;

void print(auto&& arg1, auto&& arg2) {
    cout << std::format("arg1 is: {} & arg2 is: {}\n",
        std::forward<decltype(arg1)>(arg1), std::forward<decltype(arg2)>(arg2));
}

int main() {
    string s{"Hello"};
    cout << std::format("String '{}' has {} chars\n", s, s.size());
    cout << std::format("String '{1}' has {0} chars\n", s.size(), s); // you can specify which argument you want to use for which format specifier.

    print(7.7, true); // boolean gets printed as true/false and not 1/0
    print("Rajat", '?');
    print(std::chrono::system_clock::now(), std::chrono::seconds(13)); // C++20 supports standard formatting of chrono types like durations, timepoints, and calendrical types.

    // {[ARGUMENT NO]:[FILL_CHARACTER][ALIGNMENT][SIGN - or + or space][#][0][FIELD_WIDTH][.PRECISION/SIZE][TYPE]}
    // FILL can only be used if align (left <, right >, center ^) is also used.
    // space in SIGN means print - for negative and print space for positive values.
    // # means print 0b for binaries, or 0X or 0x for hex, or 0 for octal
    // 0 is the pad character for integral types.
    cout << std::format("trying to print 56.895 as: {1:*<7.2f}\n", 5.5, 56.895); // < means left justified, precision is 2 i.e. round to 2 decimal places, TYPE is f i.e. float
    cout << std::format("trying to print 56.895 as: {1:*>7.2f}\n", 5.5, 56.895); // > means left justified.
    cout << std::format("trying to print 56.895 as: {1:*^7.2f}\n", 5.5, 56.895); // ^ means left justified.
    // strings are left justified by default, space is default fill character, field width will be 7
    // but size will be limited to 4, so only corn will be printed.
    cout << std::format("trying to print 'corner' as: {:7.4}\n", "corner");

    // print a character 'A' as decimal, hex, octal
    cout << std::format("{0} has value {0:0^18X} {0:+04d} {0:#3o}\n", '?');

    // cout << std::format("{:7.2f}\n", 42); // invalid format, trying to format an int as float.
    // good thing is that formatting error will be at compile time.

    cout << std::format("{{}}\n"); // to print raw { and }
}

/* for various formatting options for integral types, floating types, strings, chrono types, pointer types etc, refer to C++20.pdf */