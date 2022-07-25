/*
 * find the minimum element in a rotated (to the right) sorted array (in ascending order) in O(lg n) time.
 * Example:
 * [4, 5, 6, 7, 0, 1, 2] --> Ans: 0
 * All elements are given to be unique
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <optional>
using namespace std;

int solution(const vector<int>& nums, int l, int r) {
    int res{nums[0]}; // some default
    while(l <= r) {
        if(nums[l] < nums[r]) {
           res = std::min(res, nums[l]);
           break;
        }
        auto mp = (l+r) / 2;
        res = std::min(res, nums[mp]);
        if(nums[mp] >= nums[l]) {
            // nums[l]...nums[mp] is already sorted.
            l = mp+1;
        } else {
            r = mp-1;
        }
    }
    return res;
}

int main() {
   std::vector<int> nums0{0, 1, 2, 3, 4, 5, 6, 7};
   std::vector<int> nums1{7, 0, 1, 2, 3, 4, 5, 6};
   std::vector<int> nums2{6, 7, 0, 1, 2, 3, 4, 5};
   std::vector<int> nums3{5, 6, 7, 0, 1, 2, 3, 4};
   std::vector<int> nums4{4, 5, 6, 7, 0, 1, 2, 3};
   std::vector<int> nums5{3, 4, 5, 6, 7, 0, 1, 2};
   std::vector<int> nums6{2, 3, 4, 5, 6, 7, 0, 1};
   std::vector<int> nums7{1, 2, 3, 4, 5, 6, 7, 0};
   cout << "minimum in rotated sorted array: " << solution(nums0, 0, nums0.size()-1) << endl;
   cout << "minimum in rotated sorted array: " << solution(nums1, 0, nums1.size()-1) << endl;
   cout << "minimum in rotated sorted array: " << solution(nums2, 0, nums2.size()-1) << endl;
   cout << "minimum in rotated sorted array: " << solution(nums3, 0, nums3.size()-1) << endl;
   cout << "minimum in rotated sorted array: " << solution(nums4, 0, nums4.size()-1) << endl;
   cout << "minimum in rotated sorted array: " << solution(nums5, 0, nums5.size()-1) << endl;
   cout << "minimum in rotated sorted array: " << solution(nums6, 0, nums6.size()-1) << endl;
   cout << "minimum in rotated sorted array: " << solution(nums7, 0, nums7.size()-1) << endl;
   return 0;
}

