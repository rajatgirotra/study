/*
 * up until c++17, there are many ways to convert to and from string. like
 * to string
 * ========
 * sprintf, snprintf
 * std::to_string
 * std::ostringstream
 * num_put
 *
 * from string
 * ===========
 * sscanf
 * std::istringstream
 * strtol
 * atol
 * num_get
 * stoi
 *
 * all these have some or the other issue or drawbacks like
 * 1) They all are subject to locale, so even if you are just dealing with plain ascii character string, you still need to pay the price for locale handling
 * 2) some functions throw an error, other return a value like 0, false, -1 etc. Basically it isnt consistent.
 * 3) It's difficult to tell how much part of the string is getting converted etc.
 * 4) some require a format string specification.
 *
 * to overcome all this, c++17 came up with function for these conversions in the <charconv> header. we should use these almost always.
 *
 *  to convert from string to other type.
 *  ====================================
 *  std::from_chars_result from_chars(const char* first, const char* end, TYPE& value, int base = 10);
 *  TYPE could be any signed or unsigned integer type and char. base could be numbers ranging from 2 to 36.
 *
 *  std::from_chars_result from_chars(const char* first, const char* end, FLOAT_TYPE& value, std::chars_format fmt = std::chars_format::general);
 *  FLOAT_TYPE could be float, double or long double
 *  std::chars_format is enum with possible values:
 *  std::chars_format::scientific
 *  std::chars_format::fixed
 *  std::chars_format::hex
 *  std::chars_format::general = fixed | scientific
 *
 *  struct from_chars_result {
 *     const char* ptr;
 *     std::errc ec;
 *  };
 *  ptr
 *  On success, ptr points to the first character not matching the pattern. If all chars match, points to last.
 *  error code ec is value initialized if all chars matched.
 *  On failure, ptr equals first and ec = std::errc::invalid_argument.
 *  On out of range (i.e. when destination type is too small to hold the value), ec = std::err::result_out_of_range
 *  and ptr points to first character not matching the pattern
 *
 *
 *
 *  to convert from numbers to characters.
 *  =====================================
 *  std::to_chars_result to_chars(...);
 *
 */

#include <charconv>
#include <iostream>
#include <string>
using namespace std;

int main() {
    const string str("1234Rajat");
    int value{};
    auto res = std::from_chars(str.data(), str.data() + str.size(), value);
    if(res.ec == std::errc{}) {
        cout << "success, value: " << value << endl;
    } else {
        cerr << "failure, ptr: " << *res.ptr << ", ec: " << make_error_code(res.ec).message() << endl;
    }

    // enable this when your compiler supports it.
//    const string str2("16.78");
//    double value2{};
//    res = std::from_chars(str2.data(), str2.data() + str2.size(), value2, std::chars_format::general);
//    if(res.ec == std::errc{}) {
//        cout << "success, value: " << value << endl;
//    } else {
//        cerr << "failure, ptr: " << *res.ptr << ", ec: " << make_error_code(res.ec).message() << endl;
//    }
}
