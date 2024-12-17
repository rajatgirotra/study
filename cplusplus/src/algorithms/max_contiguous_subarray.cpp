/*
Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
Example 1:
Input: nums = [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
Example 2:

Input: nums = [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.

Constraints:
1 <= nums.length <= 105
nums[i] is either 0 or 1.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        // will maintain the difference between the number of 0s and 1s for every index.
        std::unordered_map<int, int> diffIndexMap{};
        int maxSubArrSize{};
        int diff{};
        for(int i = 0; i < nums.size(); ++i) {
            diff = nums[i] == 0 ? diff - 1 : diff + 1;
            if(diffIndexMap.find(diff) == diffIndexMap.end()) {
                diffIndexMap[diff] = i;
            }
            if(diff == 0) {
                maxSubArrSize = i+1;
            } else {
                auto idx = diffIndexMap[diff];
                maxSubArrSize = std::max(maxSubArrSize, i - diffIndexMap[diff]);
            }
        }
        return maxSubArrSize;
    }
};

int main() {
    Solution s;
    std::vector<int> v1{0, 1};
    std::vector<int> v2{0, 1, 0};
    cout << s.findMaxLength(v1) << endl;
    cout << s.findMaxLength(v2) << endl;
}