/*
 * write a function that takes a range and returns the maximum value in the range.
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

// a function that takes a range and returns the maximum value in the range.
template <rng::input_range Rg> // rng::input_range is a concept that guarantees that the range can be read from.
auto getMaxValue(Rg&& rg) {
    // if range is empty, throw default value of the range type
    if (rng::empty(rg)) { //helper function in std::ranges.
        return rng::range_value_t<Rg>{}; //helper function in std::ranges.
    }
    auto pos = rng::begin(rg); //helper function in std::ranges.
    auto max = *pos;
    while (++pos != rng::end(rg)) { //helper function in std::ranges.
        if (*pos > max) {
            max = *pos;
        }
    }
    return max;
}

int main() {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<int> dist(-100, 100);

    auto gen = [&] ()  mutable { return dist(rng); };

    std::vector<int> v(10);
    rng::generate(v, gen);
    std::cout << "Original vector: ";
    rng::copy(v, std::ostream_iterator<int>(std::cout, " "));

    auto max = getMaxValue(v);
    cout << "\nMax value: " << max << endl;

}

/* For continuing studying ranges and views, start at ranges_and_views_75.cpp */