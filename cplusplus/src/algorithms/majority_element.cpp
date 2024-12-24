/*
Given an array nums of size n, return the majority element.
The majority element is the element that appears more than ⌊n/2⌋ times.
You may assume that the majority element always exists in the array.

Example 1:
Input: nums = [3,2,3]
Output: 3

Example 2:
Input: nums = [2,2,1,1,1,2,2]
Output: 2

Trivial solution. use hash_map to keep the count of each element and then return the element with count > n/2.
O(n) time complexity and O(n) space complexity.

Better solution which take O(n) time complexity and O(1) space complexity is to use Boyer-Moore Voting Algorithm.
Whenever we see an element which is same as the current majority element, we increment a count.
If we see a different element, we decrement the count. If the count becomes 0, we reset the count to 1 and the majority element to the current element.
*/
#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <memory>
#include <concepts>
#include <type_traits>
#include <ranges>
#include <unordered_map>
#include <utility>

using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

class Solution {
public:
    int majorityElement1(const vector<int>& nums) {
        std::unordered_map<int, int> countMap{};
        for (auto i : nums) {
            ++countMap[i];
            if(countMap[i] > nums.size()/2) {
                return i;
            }
        }
        return 0;
    }

    int majorityElement2([[maybe_unused]] const vector<int>& nums) {
        int res{nums[0]};
        int count{1};
        for (int i = 1; i < nums.size(); ++i) {
            if (res == nums[i]) {
                ++count;
            } else {
                --count;
                if (count == 0) {
                    res = nums[i];
                    count = 1;
                }
            }
        }
        return res;
    }

};

int main() {
    Solution s;
    std::vector<int> v1{3, 2, 3};
    cout << "1st example: " << s.majorityElement1(v1) << endl;
    cout << "1st example: " << s.majorityElement2(v1) << endl;

    std::vector<int> v2{2, 2, 1, 1, 1, 2, 2};
    cout << "2nd example: " << s.majorityElement1(v2) << endl;
    cout << "2nd example: " << s.majorityElement2(v2) << endl;
}