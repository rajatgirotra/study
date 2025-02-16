/*
Given an integer array nums, return the most frequent even element.
if there is a tie, return the smallest one. If there is no such element, return -1.

Example 1:
Input: nums = [0,1,2,2,4,4,1]
Output: 2

Example 2:
Input: nums = [4,4,4,9,2,4]
Output: 4

Example 3:
Input: nums = [29,47,21,41,13,37,25,7]
Output: -1

Trivial: maintain a hashMap of counts. as you insert entries in hashMap, maintain the most frequent element which is also the smallest.
*/
class Solution {
public:
    int mostFrequentEven(vector<int>& nums) {
        std::unordered_map<int, int> m; // elem, count
        std::pair<int, int> mostFreq(-1, 0); // max elem and count so far
        for(auto num : nums) {
            if(num % 2 == 0) {
                ++m[num];
                if (mostFreq.second < m[num]) {
                    mostFreq.first = num; mostFreq.second = m[num];
                } else if(mostFreq.second == m[num]) {
                    mostFreq.first = std::min(mostFreq.first, num);
                }
            }
        }
        return mostFreq.first;
    }
};