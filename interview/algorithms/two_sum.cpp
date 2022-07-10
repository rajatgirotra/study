/*
Given an unsorted array of integers and a target sum k, find a pair of indices that sum to k.

Brute Force: O(n^2) --> Trivial, use two nested loops.
Better Way: O(n) time by using a HashMap. For every element, lookup if (k - element) is present in the map.
If yes, you have found the two pair of indices.
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
std::pair<int, int> two_sum_brute_force(std::array<int, N> arr, int k) {
    for(int i = 0; i < arr.size()-1; ++i) {
        for(int j = i+1; j < arr.size(); ++j) {
            if (arr[i] + arr[j] == k) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}

//8 8 4 18 -17 -3 -13 -7 14 4
template<size_t N>
std::pair<int, int> two_sum(std::array<int, N> arr, int k) {
    std::unordered_map<int, int> m; // key is element, value is array index
    for(int i = 0; i < arr.size(); ++i) {
        auto iter = m.find(k-arr[i]);
        if(iter != m.end()) {
            return std::make_pair(iter->second, i);
        } else {
            m.emplace(arr[i], i);
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
    
    cout << "Indices for k: " << x << ", " << y << endl;
    int k = arr[x] + arr[y];

    cout << "Elements: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "k: " << k << endl;

    auto res = two_sum(arr, k);
    cout << "Indices: [" << res.first << ", " << res.second << "]\n";

    res = two_sum_brute_force(arr, k);
    cout << "Indices (brute_force): [" << res.first << ", " << res.second << "]\n";
}
