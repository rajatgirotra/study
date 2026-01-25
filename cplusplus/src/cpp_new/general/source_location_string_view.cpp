/* Write a function which only executes at compile time and it can return the name of the template parameter.
 * One function should return the fully qualified name, the other should return just the name of the type.
 * we will use std::source_location which returns the function name, file name, line number and column at compile time.
 */

#include <print>
#include <source_location>
#include <string_view>
using namespace std;

template <typename T>
consteval auto get_func_name() {
    return std::source_location::current().function_name();
}

template <typename T>
consteval std::string_view get_type_name() {
    // res will be string_view with value = "consteval auto get_func_name() [with T = .....]
    std::string_view res = get_func_name<T>();
    auto pos = res.find("with T = ");
    auto start_pos = pos + 9; // skipping "with T = "
    if (pos != std::string_view::npos) {
        auto pos2 = res.find("]", start_pos);
        if (pos2 != std::string_view::npos) {
            return res.substr(start_pos, pos2-start_pos);
        }
    }
    return "<unknown>";
}

template <typename T>
consteval std::string_view get_short_name() {
    std::string_view res = get_type_name<T>();
    if (res.compare("<unknown>") != 0) {
        auto pos = res.rfind("::");
        if (pos != std::string_view::npos) {
            res = res.substr(pos+2);
        }
    }
    return res;
}


namespace rg {
    template <typename T>
    class TestClass {};
}

int main() {
    std::println("{}", get_short_name<rg::TestClass<int>>());
}