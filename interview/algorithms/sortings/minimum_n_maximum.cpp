// find minimum in an unordered array. How many comparisons do you need?
// Really easy. Assume min is arr[0] and compare from arr[1] to arr[n-1]. i.e.
// n-1 total comparisons.

// then find both maximum and minimum in an array. How many comparisons do you need?
// you could do n-1 individual comparisons for both maximum and minimum for a total
// of 2n-2 comparisons. but if you consider elements in pairs, you will need only
// 3n/2 total comparisons which is much better.
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
#include <cstring>
#include <utility>
using namespace std;

template <size_t N>
int minimum(int (&arr)[N]) {
    auto min = arr[0];
    for (int idx = 0; idx != N; ++idx) {
        min = arr[idx] < min ? arr[idx] : min;
    }
    return min;
}

template <size_t N>
auto minimum_n_maximum(int (&arr)[N]) {
    auto min {0}, max {0};
    if (arr[0] < arr[1]) {
        min = arr[0];
        max = arr[1];
    } else {
        min = arr[1];
        max = arr[0];
    }
    auto local_min{0}, local_max{0};
    for (int idx = 2; idx <= N-2; ++idx) {
        if(arr[idx] < arr[idx+1]) {
            local_min = arr[idx];
            local_max = arr[idx+1];
        } else {
            local_min = arr[idx+1];
            local_max = arr[idx];
        }
        if(local_min < min) {
            min = local_min;
        }
        if(local_max > max) {
            max = local_max;
        }
    }
    return std::make_pair(min, max);
}

int main() {
    std::random_device r;
    std::default_random_engine engine(r());

    std::uniform_int_distribution<int> dist(-200, 200);
    auto gen = [dist=dist, engine=engine] () mutable {
        return dist(engine);
    };

    int arr[15] {};
    std::generate(begin(arr), end(arr), gen);

    cout << "Arr: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, "  "));
    cout << endl;

    cout << "Minimum: " << minimum(arr) << endl;

    auto res = minimum_n_maximum(arr);
    cout << "Minimum n Maximum: " << res.first << ", " << res.second << endl;
}