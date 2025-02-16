/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
Example 1:
Input: nums = [3,2,3]
Output: [3]

Example 2:
Input: nums = [1]
Output: [1]

Example 3:
Input: nums = [1,2]
Output: [1,2]

Trivial solution is to maintain a hashMap of counts of every element. as you insert into hashMap, check if the count is greater than n/3,
if so, add it to the result vector.

Difficult solution is to use a hashmap of size at most 2. i.e. O(1) space. Why? If you think about it, there can be at most 2 elements
that can have count > n/3. So lets say we have [1, 2, 3, 3, 3]. We will have:
1 -> 1
2 -> 1
3 -> 1
As soon as we have a third element in the hashMap, we decrement 1 from the count and if the count drops to 0, we remove the element from the hashMap. i.e.
after we insert the third element, we actually clear the hashMap. After that we will have:
3 -> 2 and we are done.
Finally, we will have to check if the elements in the hashMap are actually greater than n/3. We can do this in a second pass. This is required. Why? lets say our array is:
[1, 2, 3, 4, 5, 6, 7, 8]. If we follow the algo above, we will have [7, 8] in the hashmap. But none of them are more than n/3 times.
Also if array is: [1, 2, 1, 2, 3, 4]: we will have:
1 -> 2
2 -> 2
3 -> 1 which changes to:
1 -> 1
2 -> 1
4 -> 1 which changes to:
EmptyHashMap. So the solution is an empty hash map.
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
    vector<int> majorityElement1(vector<int>& nums) {
        std::unordered_map<int, int> countMap{};
        std::vector<int> res{};
        for(auto i : nums) {
            ++countMap[i];
            if(countMap[i] > static_cast<int>(nums.size())/3) {
                res.emplace_back(i);
                countMap[i] = -nums.size();
            }
        }
        return res;
    }

    vector<int> majorityElement2([[maybe_unused]] vector<int>& nums) {
       std::vector<int> res{};
       return res;
    }

};

namespace {
    std::ostream& operator << (std::ostream& os, const std::vector<int>& v) {
        for(auto item : v) {
            os << item << ", ";
        }
        return os;
    }
}

int main() {
    Solution s;
    std::vector<int> v1{3, 2, 3};
    cout << "1st example: " << s.majorityElement1(v1) << endl;
    cout << "1st example: " << s.majorityElement2(v1) << endl;

    std::vector<int> v2{1};
    cout << "2nd example: " << s.majorityElement1(v2) << endl;
    cout << "2nd example: " << s.majorityElement2(v2) << endl;

    std::vector<int> v3{1, 2};
    cout << "3rd example: " << s.majorityElement1(v3) << endl;
    cout << "3rd example: " << s.majorityElement2(v3) << endl;

}