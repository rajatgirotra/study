/*
 * Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements
 * in the subarray is strictly less than k.
 *
 * Example 1:
 * Input: nums = [10,5,2,6], k = 100
 * Output: 8
 * Explanation: The 8 subarrays that have product less than 100 are:
 * [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
 * Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
 *
 * Example 2:
 * Input: nums = [1,2,3], k = 0
 * Output: 0
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // brute force
    static int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        // base case
        if (k <= 1) return 0;
        int count = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int product = 1;
            for (int j = i; j < nums.size(); ++j) {
                product *= nums[j];
                if (product < k) {
                    ++count;
                } else {
                    break;
                }
            }
        }
        return count;
    }

    static int numSubarrayProductLessThanKOptimized(vector<int>& nums, int k) {
        // base case
        if (k <= 1) return 0;
        int count = 0;
        int product = 1;
        int l = 0, r = 0;
        while (r < nums.size()) {
            product *= nums[r];
            while (product >= k) {
                product /= nums[l];
                ++l;
            }
            count += r - l + 1;
            ++r;
        }
        return count;
    }
};
int main() {
    vector<int> v1{10, 5, 2, 6};
    vector<int> v2{1, 2, 3};
    cout << "numSubarrayProductLessThanK({10, 5, 2, 6}, 100): " << Solution::numSubarrayProductLessThanK(v1, 100) << endl;
    cout << "numSubarrayProductLessThanK({1, 2, 3}, 8): " << Solution::numSubarrayProductLessThanK(v2, 0) << endl;

    cout << "numSubarrayProductLessThanKOptimized({10, 5, 2, 6}, 100): " << Solution::numSubarrayProductLessThanKOptimized(v1, 100) << endl;
    cout << "numSubarrayProductLessThanKOptimized({1, 2, 3}, 8): " << Solution::numSubarrayProductLessThanKOptimized(v2, 0) << endl;
}