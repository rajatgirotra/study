/*
Given an unsorted array of integers, find three indices such that arr[a] + arr[b] + arr[c] = 0;
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
#include <set>
using namespace std;

struct indices {
    int x {};
    int y {};
    int z {};

    explicit indices(int a, int b, int c) : x(a), y(b), z(c) {
        std::vector<int> tmp {x, y, z};
        std::sort(begin(tmp), end(tmp));
        x = tmp[0]; y = tmp[1]; z = tmp[2];
    }

    friend ostream& operator << (ostream& os, const indices& rhs) {
        os << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << "]";
        return os;
    }

    friend bool operator < (const indices& lhs, const indices& rhs) noexcept {
        return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
    }
};

template<size_t N>
std::vector<indices> three_sum_brute_force(std::array<int, N> arr) {
    std::vector<indices> res{};
    for(int i = 0; i < N-2; ++i) {
        for(int j = i+1; j < N-1; ++j) {
            for(int k = j+1; k < N; ++k) {
                if(arr[i] + arr[j] + arr[k] == 0) {
                    res.emplace_back(i, j, k);
                }
            }
        }
    }
    return res;
}


template<size_t N>
std::pair<int, int> two_sum(const std::array<int, N>& arr, int k, int ignore_idx) {
    std::unordered_map<int, int> m{}; // element and index map
    // for every element, search for K - element in hash Map.
    for(auto iter = arr.begin(); iter != arr.end(); ++iter) {
        if(distance(arr.begin(), iter) == ignore_idx) {
            continue;
        }
        auto it = m.find(k - *iter);
        if(it != m.end()) {
            return std::make_pair(it->second, std::distance(arr.begin(), iter));
        }
        m[*iter] = std::distance(arr.begin(), iter);
    }
    return std::make_pair(-1, -1);
}

template<size_t N>
std::set<indices> three_sum_optimized(const std::array<int, N>& arr) {
    std::set<indices> res{};
    for(int i = 0; i < N; ++i) {
       auto[x, y] = two_sum(arr, -1 * arr[i], i);
       if(x != -1) {
           res.emplace(i, x, y);
       }
    }
    return res;
}

template<size_t N>
std::set<indices> three_sum_optimized2(std::array<int, N> arr) {
    std::set<indices> res;
    // sort input first in O(n lg n) time
    std::sort(begin(arr), end(arr));

    for(int i = 0; i < N-2; ++i) {
        if(i > 0 && arr[i] == arr[i-1]) {
            continue;
        }
        auto l = i+1;
        auto r = arr.size() - 1;
        while(l < r) {
            auto threeSum = arr[i] + arr[l] + arr[r];
            if (threeSum < 0) ++l;
            else if (threeSum > 0) --r;
            else {
                res.emplace(i, l, r);
                l += 1;
                while(l < r && arr[l] == arr[l-1]) ++l;
            }
        }
    }
    return res;
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

    cout << "\nIndices (optimized 1):\n";
    auto res2 = three_sum_optimized(arr);
    for(auto&& i : res2) {
        cout << i << endl;
    }

    cout << "\nIndices (optimized 2):\n";
    std::sort(arr.begin(), arr.end());
    cout << "Elements: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;
    auto res3 = three_sum_optimized2(arr);
    for(auto&& i : res3) {
        cout << i << endl;
    }

}
