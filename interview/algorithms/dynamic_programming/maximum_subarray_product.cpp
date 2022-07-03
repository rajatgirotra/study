/*
In an array find a subarray with the maximum product. Example:
[-1, -2, -3] : Ans: 6
[1, 2, 3, 4]: Ans: 24
[1, -1, 0, 3, -3]: Ans: 3

Brute Force: for every element as the starting point, find all the possible subarrays.
and then compute the product of each subarray. Example: for n elements, the possible subarrays
starting at index 0 are [0, 0], [0, 1], [0, 2], [0, 3].. [0, n-1]. Subarrays starting
at index 1 are [1, 1], [1, 2].. [1, n-1]. For Brute Force will be O(n^2).

O(n) solution using DP
Note that if numbers are all positive that the subarray with the maximum product will be the complete
array itself. example: for [1, 3, 2, 3], Ans:18

When negative numbers are in the input array, you will need to keep track of both
the minimum and maximum product for any index. Why?? Lets say we have [-1, -2, -3].
Then for index 0: min=-1, max=-1
Then for index 1: min=-2, max=2 (min=-2 i.e. the element itself).
Then for index 2, if we had +3, we would have multiplied +3 with the current max(2) above to get 6
Then for index 2, if we had -3, we would have multiplied -3 with the current min instead(-2) above to get 6.
So we need to track both min, max till any index. And whichever is the curMax we need to store it in a separate variable.

If we get a 0 somewhere in the array, we can just treat it min, max as 1. as 1 is a neutral value.
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
using namespace std;

template<size_t N>
void maximum_product_subarray(int (&arr)[N]) {
    // by default we assume that max product is the element with the maximum value.
    int res = *std::max_element(begin(arr), end(arr));
    int curMin {1}, curMax {1}; // default as value 1 is neutral
    std::vector<size_t> indices; // to keep track of indices in the subarray for printing it out later.

    for(size_t idx = 0; idx < N; ++idx) {
        if(arr[idx] == 0) {
            curMin = curMax = 1;
            continue;
        }
        auto maxTmp = curMax * arr[idx];
        auto minTmp = curMin * arr[idx];
        curMax = std::max({maxTmp, arr[idx] * curMin, arr[idx]});
        curMin = std::min({maxTmp, arr[idx] * curMin, arr[idx]});
        res = std::max(curMax, res);
        cout << "curMin, curMax, res at index " << idx << ": " << curMin << ", " << curMax << ", " << res << endl;
    }

    cout << endl << "Max subarray product: " << res <<endl;
    // TODO modify to print the subarray.
}

int main() {
    int arr[15] {};

    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-4, 4);
    auto gen = [dist = dist, engine = engine] () mutable {
        return dist(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    cout << "Elements: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;
    maximum_product_subarray(arr);
}
