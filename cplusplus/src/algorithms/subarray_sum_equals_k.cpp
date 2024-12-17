/*
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
A subarray is a contiguous non-empty sequence of elements within an array.
Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2

Constraints:
1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-107 <= k <= 107
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // HashMap of prefix sum and their counts.
        std::unordered_map<int, int> prefixSumMap{};
        prefixSumMap[0] = 1;

        int runningSum{};
        int subArrayCount{};

        for(int i = 0; i < nums.size(); ++i) {
            runningSum += nums[i];
            auto diff = runningSum - k;
            if (auto iter = prefixSumMap.find(diff); iter != prefixSumMap.end()) {
                subArrayCount += iter->second;
            }
            prefixSumMap[runningSum] += 1;
        }
        return subArrayCount;
    }
};

int main() {
    Solution s;
    std::vector<int> v1{1, 1, 1};
    std::vector<int> v2{1, 2, 3};
    cout << s.subarraySum(v1, 2) << endl;
    cout << s.subarraySum(v2, 3) << endl;
}