/*
Given an integer array of size n and a window size of k, find the maximum element
in each window and return an array of the maximum values.

Brute Force: How many sliding windows will be there?? n-k+1. and window size is K
so Brute Force will be O(k.(n-k+1)). You iterate the elements in each n-k+1 sliding windows
and find the maximum.

Better way in O(n): We maintain a deque of elements and their index in the input array. As we traverse the input array,
we keep adding the element and its index in the deque. But before adding we pop any elements less than the current value.
and also pop any elements which are out of bounds of the sliding window. Then as we reach k elements (i.e. the first sliding window),
after that we start peeking the first element in the deque in each iteration and put it in our output array.
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
#include <vector>
#include <cassert>
using namespace std;

template <size_t N>
auto sliding_window_brute_force(const std::array<int, N>& arr, int K) {
    std::vector<int> res;
    res.reserve(N-K+1);

    for(int i = 0; i < N-K+1; ++i) {
        res.push_back(*std::max_element(std::next(begin(arr),i), std::next(begin(arr), i + K)));
    }
    return res;
}

template <size_t N>
auto sliding_window_optimized(const std::array<int, N>& arr, int K) {
    std::vector<int> res;
    res.reserve(N-K+1);

    std::deque<std::pair<int, int>> staging{};

    for(int i = 0 ; i < N; ++i) {
        // while staging is not empty remove any elements that are less than the current element
        while(!staging.empty() && staging.back().first < arr[i])
            staging.pop_back();

        // also remove any elements from the front where the index are less than the start of the current sliding window
        while(!staging.empty() && staging.front().second <= (i - K)) {
            staging.pop_front();
        }

        // put your element
        staging.emplace_back(arr[i], i);

        // populate output
        if(i >= K-1) {
            res.push_back(staging.front().first);
        }
    }

    return res;
}

int main() {
    std::array<int, 10> arr{};
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-6, 6);
    auto gen = [dist = dist, engine = engine] () mutable {
        return dist(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    cout << "Elements: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;

    auto res = sliding_window_brute_force(arr, 2);
    auto res2 = sliding_window_optimized(arr, 2);
    assert(res == res2);
    cout << "sliding window maximum array with window: " << 2 << endl;
    for(auto&& val : res) {
        cout << val << "  ";
    }
    cout << endl;

    std::array<int, 12> x {1, 1, 1, 1, 1, 4, 3, 2, 1, 0, -1, -2};
    auto res3 = sliding_window_brute_force(x, 6);
    auto res4 = sliding_window_optimized(x, 6);
    assert(res3 == res4);
    cout << "sliding window maximum array with window: " << 2 << endl;
    for(auto&& val : res3) {
        cout << val << "  ";
    }
    cout << endl;
}
