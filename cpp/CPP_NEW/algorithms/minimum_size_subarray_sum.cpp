/*
 * Given an array of positive integers nums and a positive integer target, return the minimal length of a
 * subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.
 *
 * Input: target = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: The subarray [4,3] has the minimal length under the problem constraint.
 *
 * Input: target = 4, nums = [1,4,4]
 * Output: 1
 *
 * Input: target = 11, nums = [1,1,1,1,1,1,1,1]
 * Output: 0
 */

#include <random>
#include <iostream>
#include <cstdint>
#include <array>
#include <algorithm>
#include <iterator>
using namespace std;

/* Brute force way will be O(n2). We can traverse all subarray starting at index 0,
 * then all subarrays starting at index 1, then index 2 and so on. and keep record of minimum subarray
 */
template <size_t N>
int minimum_size_subarray_sum_brute_force(const std::array<int, N>& arr, int target) {
    // for every subarray see if we can find the target.
    auto min_subarray_len {arr.size() + 1};
    for(auto start_index = 0ul; start_index < N; ++start_index) {
        auto sum{0};
        for(auto end_index = start_index; end_index < N; ++end_index) {
            sum += arr[end_index];
            if(sum >= target) {
                min_subarray_len = std::min(min_subarray_len, end_index - start_index + 1);
            }
        }
    }
    if(min_subarray_len == arr.size() + 1) return 0;
    else return min_subarray_len;
}

/*
 * O(n) solution using sliding window.
 */
template <size_t N>
int minimum_size_subarray_sum_sliding_window(const std::array<int, N>& arr, int target) {
    auto l {0ul};
    auto total{0ul};
    auto res{arr.size() +  1};

    for(auto r = 0ul; r < arr.size(); ++r) {
        total += arr[r];
        while (total >= target) {
            res = std::min(res, r-l + 1);
            total -= arr[l];
            ++l;
        }
    }
    return ((res == arr.size() + 1) ? 0 : res);
}

int main() {
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(1, 6);
    std::uniform_int_distribution<int> dist2(5, 27);

    std::array<int, 7> arr{};
    auto gen = [&dist, &engine] () {
        return dist(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    cout << "Input arr:";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    auto target = dist2(engine);
    cout << "\nTarget: " << target << endl;

    auto res = minimum_size_subarray_sum_brute_force(arr, target);
    cout << "subarray length brute force: " << res << endl;

    auto res2 = minimum_size_subarray_sum_brute_force(arr, target);
    cout << "subarray length sliding window: " << res2 << endl;

}

