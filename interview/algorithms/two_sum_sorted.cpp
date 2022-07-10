/*
Given a sorted array of integers and a target sum k, find a pair of indices that sum to k.

Trivial: Just like two_sum but array is sorted. So we can use the two pointer approach. One points to first
and the other points to last. Then we can increment first and decrease last as the case need be.
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
using namespace std;

template<size_t N>
std::pair<int, int> two_sum_sorted(std::array<int, N> arr, int k) {
    auto first = arr.begin();
    auto last = arr.end();
    --last;
    while (first < last) {
        if ((*first + *last) < k) {
            ++first;
        } else if ((*first + *last) > k) {
            --last;
        } else {
            // we found the indices
            return std::make_pair(std::distance(arr.begin(), first), std::distance(arr.begin(), last));
        }
    }
    return std::make_pair(-1, -1);
}


int main() {
    std::array<int, 10> arr{};
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-20, 20);
    auto gen = [dist = dist, engine = engine] () mutable {
        return dist(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    // get two random indices between 0 and 10
    std::uniform_int_distribution<int> dist2(0, 9);
    int x = dist2(engine);
    int y = x;
    do {
        y = dist2(engine); // if index x and y are same, we wil never be able to find two sum.
    } while(x == y);
    
    int k = arr[x] + arr[y];

    std::sort(arr.begin(), arr.end());
    cout << "Elements: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "k: " << k << endl;

    auto res = two_sum_sorted(arr, k);
    cout << "Indices: [" << res.first << ", " << res.second << "]\n";
}
