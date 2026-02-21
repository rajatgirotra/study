#include <print>
#include <string>
#include <string_view>
#include <array>
using namespace std::literals;

struct Data {
    int m_age;
    std::string m_name;
    bool m_married;
    constexpr static std::array<std::string_view, 3> names {"m_age"sv, "m_name"sv, "m_married"sv};
};

template <typename First, typename Second>
struct Pair {
    First first;
    Second second;

    constexpr static std::array<std::string_view, 2> names {"first"sv, "second"sv};
};

template <typename Object>
void visit(auto Visitor, Object&& obj) {
    if constexpr(obj.names.size() == 0) {}
    else if constexpr(obj.names.size() == 1) {
        auto&& [m0] = std::forward<Object>(obj);
        Visitor(obj.names[0], std::forward<decltype(m0)>(m0));
    }
    else if constexpr(obj.names.size() == 2) {
        auto&& [m0, m1] = std::forward<Object>(obj);
        Visitor(obj.names[0], std::forward<decltype(m0)>(m0));
        Visitor(obj.names[1], std::forward<decltype(m1)>(m1));
    }
    else if constexpr(obj.names.size() == 3) {
        auto&& [m0, m1, m2] = std::forward<Object>(obj);
        Visitor(obj.names[0], std::forward<decltype(m0)>(m0));
        Visitor(obj.names[1], std::forward<decltype(m1)>(m1));
        Visitor(obj.names[2], std::forward<decltype(m2)>(m2));
    }
}

// with c++26 and support for variadic structured bindings, this becomes very easy.
template <typename Object>
void visit_cpp26(auto Visitor, Object&& obj) {
    if constexpr(obj.names.size() > 0) {
        auto&& [...values] = std::forward<Object>(obj);
        int count = 0;
        (Visitor(obj.names[count++], values), ...);
    }
}


int main() {
    Data d{.m_age = 41, .m_name = "Rajat" , .m_married = true};
    Pair<int, double> p{100, 5.5};

    auto visitor = [](std::string_view name, auto&& value) {
        std::print("name: {}, value: {}\n", name, value);
    };

    visit(visitor, d);
    visit(visitor, p);
}
