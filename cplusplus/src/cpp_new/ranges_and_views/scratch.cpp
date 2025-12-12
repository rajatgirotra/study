#include <print>
#include <ranges>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <deque>
#include <cxxabi.h>
#include <string>
#include <string_view>
#include <tuple>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::ranges::views;

string demangle(const char *mangled_name) {
    int res = -1;
    auto s = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &res);
    if (res) {
        std::print("abi::__cxa_demangled failed with return code {}", res);
    }
    string rstr(s);
    free(s);
    return rstr;
}

class S {
public:
    S() { std::print("S::S()\n"); }

    ~S() {
        std::print("S::~S()\n");
        m_v.clear();
    }

    S(const S &) { std::print("S(const S&)\n"); }
    S(S &&) { std::print("S(S&&)\n"); }

    std::vector<int> m_v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
};


auto getData() {
    // return S();
    return std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
}


int main() {
    std::vector intVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    auto v1 = vws::take(intVec, 5);
    // auto v1 = vws::take(getData(), 5);
    rng::copy(v1, ostream_iterator<int>(cout, " "));

    cout << endl;
    // auto v2 = vws::filter(intVec, [](auto&& elem) { return elem%3==0; });
    auto v2 = vws::filter(getData(), [](auto &&elem) { return elem % 3 == 0; });
    rng::copy(v2, ostream_iterator<int>(cout, " "));

    cout << endl;
    // auto v3 = vws::transform(intVec, [](const auto& elem) { return elem*elem; });
    auto v3 = vws::transform(getData(), [](const auto &elem) { return elem * elem; });
    rng::copy(v3, ostream_iterator<int>(cout, " "));

    std::vector<std::tuple<int, char, string> > tVec{
        {1, 'A', "α"},
        {2, 'B', "β"},
        {3, 'C', "γ"},
        {4, 'D', "δ"},
        {5, 'E', "ε"},
    };

    cout << endl;
    auto elem = vws::elements<1>(tVec);
    std::println("type of elem {}", demangle(typeid(elem).name()));
    rng::copy(elem, ostream_iterator<rng::range_value_t<decltype(elem)> >(cout, " "));

    // views can be nested. create a view of only elements that are divisible by 3. square them and choose only the first 2.
    cout << endl;
    auto final_view = vws::take(
        vws::transform(
            vws::filter(getData(), [](const auto &e) { return e % 3 == 0; }),
            [](const auto &e) { return e * e; })
        , 2);
    rng::copy(final_view, ostream_iterator<rng::range_value_t<decltype(final_view)> >(cout, " "));

    std::println();
    auto final_view_2 = getData()
                        | vws::transform([](const auto &e) { return e * e; })
                        | vws::filter([](const auto &e) { return e % 3 == 0; })
                        | vws::take(2);
    rng::copy(final_view_2, ostream_iterator<rng::range_value_t<decltype(final_view_2)> >(cout, " "));
}
