/*
Longest increasing subsequence. example: [10, 22, 9, 33, 21, 50, 41, 60]
A subsequence is any sub-array which may not be necessarily contiguous.
We need to find the length and the subsequence of largest length

Brute Force will be O(2^n). as we have 2^n possible subsets of n element array

Here we use dynamic programming to find an O(n^2) solution which is much better.
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

template <size_t N>
void longest_increasing_subsequence(int (&arr)[N]) {
    // lis is an array here lis[k] is the length of Longest Increasing Subsequence
    // beginning at k. 
    int lis[N] {};
    std::fill(begin(lis), end(lis), 1); // lis[k] = 1 by default.
    int lis_idx[N] {-1};
    std::fill(begin(lis_idx), end(lis_idx), -1);
    for(int i = N-1; i >= 0; --i) {
        for(int j = i + 1; j < N; ++j) {
            if(arr[i] < arr[j]) {
                if(lis[i] < 1 + lis[j]) {
                    lis[i] = 1 + lis[j];
                    lis_idx[i] = j;
                }
            }
        }
    }
    auto max_idx = 0;
    auto max_lis = lis[0];
    for(int i = 1; i < N; ++i) {
        if(max_lis < lis[i]) {
            max_idx = i;
            max_lis = lis[i];
        }
    }
    cout << "\nLongest increasing subsequence length: "  << max_lis << endl;
    cout << "Longest increasing subsequence: ";
    cout << arr[max_idx] << "  ";    
    while(lis_idx[max_idx] != -1) {
        cout << arr[lis_idx[max_idx]] << "  ";
        max_idx = lis_idx[max_idx];
    }
}

int main() {
    int arr[15] {};

    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(0, 15);
    auto gen = [dist = dist, engine = engine] () mutable {
        return dist(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    cout << "Elements before\n";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;
    longest_increasing_subsequence(arr);
}
