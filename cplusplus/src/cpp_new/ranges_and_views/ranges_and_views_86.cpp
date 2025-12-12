/*
 * DOs and DON'ts with views
 */
#include <iostream>
#include <concepts>
#include <ranges>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cxxabi.h>
#include <cassert>
#include <random>
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

auto getValues()
{
    std::vector coll{1, 2, 3, 4, 5};
    // return coll | std::views::drop(2); // ERROR: return reference to local range.
    // since coll is an lvalue, the resulting view would be a ref_view.

    // return std::move(coll) | std::views::drop(2); // This is OK.
}

// auto getValues()
// {
//     return std::vector {1, 2, 3, 4, 5} | std::views::drop(2); // OK
//     // the resulting view will be an owning_view.
// }

int main() {
}

