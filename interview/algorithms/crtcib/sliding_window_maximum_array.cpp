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
using namespace std;

template<size_t N, size_t K>
void sliding_window_brute_force(std::array<int, N> arr) {
    int max_arr [N-K+1] {};
    for(int i = 0; i < N-K+1; ++i) {
        max_arr[i] = *std::max_element(next(arr.begin(), i), next(arr.begin(), i+K));
    }
    cout << "Max Sliding Window Brute Force: ";
    std::copy(begin(max_arr), end(max_arr), ostream_iterator<int>(cout, "  "));
    cout << endl;
}

template<size_t N, size_t K>
void sliding_window_optimized(std::array<int, N> arr) {
    std::vector<int> max_arr{};
    std::deque<std::pair<int, int>> staging {};
    // traverse the whole input array
    for(int i = 0; i < N; ++i) {
        // while staging is not empty and the values in staging are less than the current value,
        // keep popping
        while (!staging.empty() && staging.back().first < arr[i]) {
            staging.pop_back();
        }

        // Also pop elements from the front which are out of bounds of the current sliding window.
        if(!staging.empty() && i - staging.front().second >= K) {
            staging.pop_front();
        }

        // add element
        staging.push_back(std::make_pair(arr[i], i));

        if(i + 1 >= K) {
            max_arr.push_back(staging.front().first);
        }
    }
    cout << "Max Sliding Window Optimized: ";
    std::copy(begin(max_arr), end(max_arr), ostream_iterator<int>(cout, "  "));
    cout << endl;
}


int main() {
    std::array<int, 8> arr{};
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

    sliding_window_brute_force<arr.size(), 2>(arr);
    sliding_window_optimized<arr.size(), 2>(arr);
    // std::array<int, 12> x {1, 1, 1, 1, 1, 4, 3, 2, 1, 0, -1, -2};
    // sliding_window_brute_force<12, 6>(x);
    // sliding_window_optimized<12, 6>(x);
}
