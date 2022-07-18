/*
Non decreasing subarray:
Given an array of ints, check if the array can be made NON-DECREASING with maximum one edit.
NON-DECREASING MEANS: arr[i] <= arr[i+1]
Example: [3, 4, 4, 5]

Consider: [2, 4, 2, 2] --> We compare elements in pairs.
[2, 4] --> OK
[4, 2] --> NOT OK, either we change 4 to 3 or 2 or we increase 2 to 4 or higher. What should we do? We should always prefer
to decrease the left element, otherwise if we increase the right element, the following element may become less than
the new right, reducing our chances to make a NON-DECREASING array; as in this case.

When decreasing the left element, we can only go as low as the element before it. And when increasing the right element, 
we can only go as high as the left element (because we dont want to go uncessarily to a very high value). Lets' try.
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
#include <cstring>
#include <utility>
#include <ctime>
#include <array>
#include <deque>
#include <cassert>
#include <unordered_map>
#include <ostream>
#include <string>
using namespace std;

template <size_t N>
bool non_decreasing_arr_possible(std::array<int, N>& arr) {
    // check elements in pairs
    bool changed {false};
    for(size_t i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] <= arr[i+1]) {
            continue; // normal case
        }
        // we need to make a change; but have we made a change already
        if (changed) {
            cout << "\nModified arr: ";
            std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
            return false;
        }

        // try to decrease left element first
        if(i == 0 || arr[i-1] <= arr[i+1]) {
            arr[i] = arr[i+1];
        } else {
            // increase right element
            arr[i+1] = arr[i];
        }
        changed = true;
    }
    cout << "\nModified arr: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
    return true;
}

int main() {
    std::array<int, 6> arr{};

    std::random_device r;
    std::default_random_engine engine(r());

    std::uniform_int_distribution dist(0, 6);
    auto gen = [dist = std::move(dist), engine = std::move(engine)]  () mutable {
        return dist(engine);
    };

    std::generate(begin(arr), end(arr), gen);

    cout << "Array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
    auto res = non_decreasing_arr_possible(arr);
    cout << "\nNon decreasing array possible: " << std::boolalpha << res << endl;
}
