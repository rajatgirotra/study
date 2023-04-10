/* find the maximum contiguous subarray of size k in an array of size n
   very trivial. compute the maximum of all possible subarray's of size k. and maintain a maximum. It will take O(n.k)

   better way: compute arr[0] + arr[1] + arr[2] +.. + arr[k].
   then for each index i from k to n, adjust the sum by adding arr[i] and subtracting arr[i-k]
*/

#include <iostream>
#include <array>
#include <random>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <utility>
#include <iterator>
using namespace std;

template <auto N>
auto max_contiguous_subarr_k_brute_force(std::array<int, N> arr, int k) {
    // There will be N-k+1 sub arrays of size k.
    // visit every subarray and keep count of maximum
    assert(k <= N);
    auto maxSum = std::numeric_limits<int>::min();
    auto res = std::make_pair(-1, -1);
    for(int i = 0; i < N-k+1; ++i) {
        auto tmpSum{0};
        auto j{i};
        for(j = i; j < k + i; ++j) {
            tmpSum += arr[j];
        }
        if(tmpSum > maxSum) {
            maxSum = tmpSum;
            res = std::make_pair(i, i+k-1);
        }
    }
    return res;
}

template <auto N>
auto max_contiguous_subarr_k_optimized(std::array<int, N> arr, int k) {
    // There will be N-k+1 sub arrays of size k.
    // we will find the first subarray sum and store that as result.
    // then for every other subarray we will remove the first element and add the current element
    assert(k <= N);
    auto maxSum = std::accumulate(begin(arr), std::next(begin(arr), k), 0);
    auto runningSum = maxSum;
    auto res = std::make_pair(0, k-1);
    for(int i = k; i < N; ++i) {
        runningSum = runningSum - arr[i-k] + arr[i];
        if(runningSum > maxSum) {
            maxSum = runningSum;
            res = std::make_pair(i-k+1, i);
        }
    }
    return res;
}


int main() {

    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution dist(-9, 9);
    std::array<int, 8> arr{5, 9, 9, -5, 6, 8, -7, 0};

    auto gen = [&]() {
        return dist(engine);
    };

    (void)gen;
//    std::generate(begin(arr), end(arr), gen);

    cout <<"Input array: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;

    int k = 4;

    auto res = max_contiguous_subarr_k_brute_force(arr, k);
    cout << "max_sum is from index " << res.first << " to " << res.second << ": " << std::accumulate(begin(arr)+res.first, begin(arr)+res.first+k, 0) << endl;

    auto res2 = max_contiguous_subarr_k_optimized(arr, k);
    cout << "max_sum is from index " << res2.first << " to " << res2.second << ": " << std::accumulate(begin(arr)+res2.first, begin(arr)+res2.first+k, 0) << endl;
}
