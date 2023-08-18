/*
 * Projections:
 * Most of the std::ranges::algorithms() take a final argument which is a projection. It is way to transform the value processed by the algorithm.
 * Example: Lets say you have a sequence of positive and negative numbers, and you want to sort them. But during sorting, you want to consider their absolute values.
 * So you have two choices.
 * 1) Introduce your own lambda comparator
 * 2) Introduce a projection where you return the absolute value of the element. the sort algorithm will then use this positive value during sorting. i.e.
 *    User-defined projections simply have to take one parameter and return a value for the transformed parameter.
 */
#include <iostream>
#include <ranges>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>
#include <random>
#include <iterator>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

int main() {
    vector<int> coll(10);

    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-10, 10);
    auto gen = [&engine, &dist] () {
        return dist(engine);
    };
    std::ranges::generate(coll, gen);

    cout << "Original array: ";
    std::ranges::copy(coll, ostream_iterator<int>(cout, " "));
    cout << endl;

    // sort elements in descending order but with custom compartor
    std::ranges::sort(coll, [](const auto& a, const auto& b) {
       return std::abs(a) >= std::abs(b);
    });

    cout << "sorted array in descending order: ";
    std::ranges::copy(coll, ostream_iterator<int>(cout, " "));
    cout << endl;

    // sort elements in ascending order but with a projection
    std::ranges::sort(coll, std::ranges::less{}, [](const auto& arg) {
        return abs(arg);
    });
    cout << "sorted array in ascending order: ";
    std::ranges::copy(coll, ostream_iterator<int>(cout, " "));
    cout << endl;

}
