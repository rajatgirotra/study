/*
 * You have already seen how to create a range with an iterator and sentinel using std::ranges::subrange.
 * Similarly to create a range with an iterator and count, the easiest way is to use the range adaptor function
 * std::views::counted(). It creates a view to the first n elements starting at some begin iterator/pointer.
 */
#include <iostream>
#include <ranges>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

int main() {
    vector intVec{1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto range = vws::counted(std::next(intVec.begin(), 5), 3); // begin iterator at value 6 and count = 3
    for(auto&& i : range) {
        cout << i << " ";
    }
    cout << endl;

    // sort the range in reverse
    std::ranges::sort(range, std::ranges::greater{});
    for(auto&& i : intVec) {
        cout << i << " ";
    }
    cout << endl;
    // note how all the ranges are reference ranges. any modifications write through the underlying collection.
}
