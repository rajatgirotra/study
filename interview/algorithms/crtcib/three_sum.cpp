/*
Given an usorted array of integers find three indices such that arr[a] + arr[b] + arr[c] = 0;
DO NOT RETURN DUPLICATE TRIPLETS.

Brute force: O(n^3),

Better: for every element, call two_sum(). Two_sum returns in O(n) time, so total complexity will be O(n^2).

Another solution: sort the array first O(n log n), then use two_sum_sorted() on every element (using Left and right pointers) which takes O(n)
So overall will still be O(n^2)
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
using namespace std;

struct indices {
    int x {};
    int y {};
    int z {};

    explicit indices(int a, int b, int c) : x(a), y(b), z(c) {};

    friend ostream& operator << (ostream& os, const indices& rhs) {
        os << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << "]";
        return os;
    }
};

template<size_t N>
std::vector<indices> three_sum_brute_force(std::array<int, N> arr) {
    std::vector<indices> v;
    for(int i = 0; i < arr.size() - 2; ++i) {
        for(int j = i+1; j < arr.size() - 1; ++j) {
            for(int k = j+1; k < arr.size(); ++k) {
                if(arr[i] + arr[j] + arr[k] == 0) {
                    v.emplace_back(arr[i], arr[j], arr[k]);
                }
            }
        }
    }
    return v;
}

template<size_t N>
std::vector<indices> three_sum_optimized(std::array<int, N> arr) {
    std::sort(arr.begin(), arr.end());
    std::vector<indices> v;
    for(int i = 0; i < arr.size() - 2; ++i) {
        if(i > 0 && arr[i] == arr[i-1]) {
            continue;
        }
        int left = i + 1;
        int right = arr.size() - 1;
        while(left < right) {
            auto sum = arr[i] + arr[left] + arr[right];
            if(sum > 0) {
                --right;
            } else if (sum < 0) {
                ++left;
            } else {
                v.emplace_back(arr[i], arr[left], arr[right]);
                do {
                    ++left; // [-2, -2, 0, 0, 2, 2], [-3, -3, 1, 2, 3, 4], [-3, -3, -1, 0, 1, 2, 4]
                } while(left < right && arr[left-1] == arr[left]);
                
            }
        }
    }
    return v;
}


int main() {
    std::array<int, 7> arr{3, -3, -1, 0, 1, 2, 4};

    // std::sort(arr.begin(), arr.end());
    cout << "Elements: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << "\nIndices (brute force):\n";
    auto res = three_sum_brute_force(arr);
    for(auto&& i : res) {
        cout << i << endl;
    }
    cout << "\nIndices (optimized):\n";
    res = three_sum_optimized(arr);
    for(auto&& i : res) {
        cout << i << endl;
    }
}
