#include <iostream>
#include <concepts>
#include <ranges>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cxxabi.h>
#include <cassert>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

string demangle(const char* const mangled_name) {
    int res = -1;
    auto str = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &res);
    assert(res == 0);
    string ret(str);
    free(str);
    return ret;
}

auto getData() {
    return std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
}

int main() {
    std::vector<int> intVec {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto pos1 = rng::find(getData(), 3);
    static_assert(std::is_same_v<decltype(pos1), rng::borrowed_iterator_t<std::vector<int>>>);
    static_assert(std::is_same_v<decltype(pos1), rng::dangling>);

    std::vector<int>::iterator pos{};
    {
        auto rg_first_2 = vws::take(intVec, 5);
        pos = rng::find(rg_first_2, 3);
        cout << "A value " << *pos << " found at index " << std::distance(begin(intVec), pos) << endl;
        // trivial to understand
    }

    std::vector<int>::iterator pos2{};
    {
        auto rg_first_2 = vws::take(getData(), 5);
        pos2 = rng::find(rg_first_2, 3);
        cout << "value " << *pos2 << " found at index " << std::distance(begin(intVec), pos2) << endl;
    }

    cout << "value " << *pos2 << " found at index " << std::distance(begin(intVec), pos2) << endl;
}