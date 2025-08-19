/*
 * if you can't have a compile time format string, use std::vformat() set of functions instead.
 * The downside is that formatting errors will now be thrown at run time. std::format_error exception will be thrown.
 */

#include <iostream>
#include <format>
using namespace std;

int main() {
    const char* fmt1 = "{:7.2f}\n"; // note that fmt1 is not compile time string. constexpr char* fmt1 is
    auto value = 42; // 42.
    cout << std::vformat(fmt1, std::make_format_args(value)); // cppreference and c++20 gcc code, both show that this function
    // only accepts lvalues.
}
