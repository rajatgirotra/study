/*
 * let's iterate over a sequence of heterogenous type.
 */
#include <print>
#include <tuple>
#include <typeinfo>
#include <cxxabi.h>
#include <string>
#include <cassert>

using namespace std;

namespace {
    auto demangle(const char* mangled_name) -> string {
        int res{};
        char* demangled = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &res);
        assert(res == 0);
        string demangled_name(demangled);
        free(demangled);
        return demangled_name;
    }
}

template <typename T>
void print_type_and_value(T&& t) {
    std::println("type: {}, value: {}", demangle(typeid(t).name()), std::forward<T>(t));
}

template <typename... Args>
void print_tpl(const std::tuple<Args...>& tpl) {
    (print_type_and_value(std::get<Args>(tpl)), ...);
}

// c++26 also introduces expansion pack in a structured binding.
// this is really iteration over heterogeneous types which you can also achieve using "template for".
void use_data(const auto& data) {
    const auto& [...elem] = data;
    (print_type_and_value(elem), ...);
}

void use(double) { std::println("using double"); }
void use(int)  { std::println("using int"); }
void use(char)  { std::println("using char"); }

struct Data {
    char a;
    char b;
    double c;
    int x;
    int y;
};

auto get_data() -> Data {
    return Data{.a = 'A', .b = 'B', .c = 3.14, .x = 42, .y = 43};
}

consteval auto get_constexpr_data() -> Data { // really really constexpr at compile time
    return Data{.a = 'A', .b = 'B', .c = 3.14, .x = 42, .y = 43};
}

template <auto Value>
auto use_constexpr() { use(Value); }


int main() {
    std::tuple<int, double, char> tpl{10, 5.5, 'A'};

    std::println("----------------- print tuple using variadic template -------------------");
    print_tpl(tpl);
    // so you have to do parameter pack expansion above.

    // c++26 introduces "template for" to iterate over heterogeneous types using a simple for loop.
    // works in godbolt gcc-trunk but not on gcc 15.2.0
    std::println("----------------- template for on tuple -------------------");
    template for (const auto& val : tpl) {
        print_type_and_value(val);
    }

    std::println("----------------- template for on tuple 2 -------------------");
    template for (const auto& val : tpl) {
        use(val); // if you only have use(double) declared, it will result in implicit conversions from int->double, and char->double
    }

    // where else could you have heterogeneous types?
    // structured bindings... 🙂
    std::println("----------------- template for on structured bindings -------------------");
    template for (const auto& val : get_data()) {
        use(val);
    }

    std::println("----------------- non template for solution -------------------");
    use_data(get_data());

    // the real strength of "template for" is when you want to iterate over const expressions (constexpr)
    std::println("----------------- template for over constexpr -------------------");
    // [[maybe_unused]] constexpr auto constexpr_data = get_constexpr_data(); // wont work without static
    // error: address of non-static constexpr variable 'constexpr_data' may differ on each invocation of the enclosing function; add 'static' to give it a constant address
    [[maybe_unused]] constexpr static auto constexpr_data = get_constexpr_data();
    template for (constexpr auto val : constexpr_data) {
        use_constexpr<val>();
    }
}
