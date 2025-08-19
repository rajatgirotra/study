/*
 * the problem with std::format() is that it allocates a string. to prevent allocation we can use std::format_to_n()
 * which takes a buffer and size (how many bytes to write in the buffer). the return type is a struct which has fields:
 * out --> the pointer of first entry in the buffer which is not written to. i.e. *(ret.out) = '\0' to null terminate the buffer
 * size --> number of characters that would have been written without truncating them to the size (passed in as argument).
 * i.e. the size of the complete formatted string.
 */

#include <iostream>
#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <chrono>
#include <iterator>
using namespace std;

void print(auto&& arg1, auto&& arg2) {
    cout << std::format("arg1 is: {} & arg2 is: {}\n",
        std::forward<decltype(arg1)>(arg1), std::forward<decltype(arg2)>(arg2));
}

int main() {
    char buffer[64]{};

    string str("Hello");
    auto ret = std::format_to_n(buffer, std::size(buffer)-1, "String '{}' has {} chars", str, str.size());
    *(ret.out) = '\0';
    cout << "buffer: " << buffer << ", ret.size: " << ret.size << "\n";

    // another variation available is std::format_to() which can write unlimited amount of chars to the first an output iterator for chars.
    // this iterator is passed as the first argument.
    std::format_to(std::ostreambuf_iterator<char>(cout), "String '{}' has {} chars\n", str, str.size());

    // will give you the size of the formatted string, without writing anything.
    auto sz = std::formatted_size("String '{}' has {} chars\n", str, str.size());
    cout << "sz: " << sz << "\n";
}
