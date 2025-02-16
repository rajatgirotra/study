/*
Given an integer array nums, return the length of the longest strictly increasing subsequence
Example 1:

Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
Example 2:

Input: nums = [0,1,0,3,2,3]
Output: 4
Example 3:

Input: nums = [7,7,7,7,7,7,7]
Output: 1
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>

using namespace std;

namespace rng = std::ranges;
namespace vws = std::views;

//O(n2) solution
int lengthOfLIS(vector<int> &nums) {
    std::vector<int> dp(nums.size(), 1);
    for (int i = 1; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = std::max(dp[i], dp[j]+1);
            }
        }
    }
    return *rng::max_element(dp);
}

// O(nlgn) solution
int lengthOfLIS2(vector<int> &nums) {
    std::vector<int> dp;
    dp.reserve(nums.size());
    for (int num : nums) {
        auto iter = rng::lower_bound(dp, num);
        if (iter == dp.end()) {
            dp.emplace_back(num);
        } else {
            *iter = num;
        }
    }
    cout << "LIS: ";
    // rng::copy(dp, ostream_iterator<int>(cout, ", "));
    return dp.size();
}




int main() {
    vector<int> v1{10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> v2{0, 1, 0, 3, 2, 3};
    vector<int> v3{7, 7, 7, 7, 7, 7, 7};

    cout << "lengthOfLIS(10, 9, 2, 5, 3, 7, 101, 18): " << lengthOfLIS(v1) << " " << lengthOfLIS2(v1) << endl;
    cout << "lengthOfLIS(0, 1, 0, 3, 2, 3): " << lengthOfLIS(v2) << " " << lengthOfLIS2(v2) << endl;
    cout << "lengthOfLIS(7, 7, 7, 7, 7, 7, 7): " << lengthOfLIS(v3) << " " << lengthOfLIS2(v3) << endl;
}
