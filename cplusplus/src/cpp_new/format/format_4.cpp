/*
 * std::format() can be used with user defined types. for that all you need to do is create a template specialization
 * for of the std::formatter<> for your user defined class
 */

#include <iostream>
#include <format>
#include <string>
using namespace std;

class Always42 {
    public:
    auto getValue() const noexcept -> int { return 42; }
};

template <>
struct std::formatter<Always42> {
    /* both parse and format take a context object: format_parse_context and format_context
    parse() must be constexpr because the std::format() format string should be a compile time constant.
    which means parse() should also be callable at compile time.
    format_parse_context provides a ctx object with begin(), end() functions. begin() points to the first location in the format string
    after the opening brace (and any argument number selector), example:

    in "{0:7d}"       -- ctx.begin() points to 7d},
    in "{0:7.2f}"     -- ctx.begin() points to 7.2f,
    in "{0} {0}"      -- ctx.begin() points to 0} {0},
    in {1:_20>}cm \n" -- ctx.begin() points to _20>}cm \n

    ctx.end() points to the end of the whole format string. your aim is to parse this format. and return the pointer to the closing brace,
    so std::format() can continue from there to format other arguments.
    */
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin(); // right now we are just returning ctx.begin() which we will fix
    }

    auto format(const Always42& obj, std::format_context& ctx) {
        return std::format_to(ctx.out(), "{:d}", obj.getValue()); // ctx.out is the location where the output is ocurring.
    }
};