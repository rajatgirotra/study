/*
* Find all the contiguous subarray's which sum up to given value k
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int subarray_sum_equals_k(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> m;
    m.emplace(0, 1);
    auto sum{0};
    auto res{0};
    for(auto&& val : nums) {
        sum += val;
        //cout << "sum: " << sum << endl;
        auto iter = m.find(sum-k);
        if(iter != m.end()) {
            res += iter->second;
        }
        m[sum] += 1;
    }
    return res;
}

int main() {
    std::vector<int> nums {1, -1, 1, 1, 1, 1};
    int k = 3;
    cout <<	subarray_sum_equals_k(nums, k) << endl;
}

/*
 * p[0] = 1
 * sum = 1
 * p has sum-k (1-3 = -2). No
 * p[sum] += 1
 * p[1] = 1
 *
 * sum = sum + nextElem
 * sum = 1 + -1 = 0
 * p has sum-k (0-3 = -3). No
 * p[0] = 2

 * sum = sum + nextElem
 * sum = 1 + -1 + 1 = 1
 * p has sum-k (1-3 = -2). No
 * p[1] = 2

 * sum = sum + nextElem
 * sum = 1 + -1 + 1 + 1= 2
 * p has sum-k (2-3 = -1). No
 * p[2] = 1

 * sum = sum + nextElem
 * sum = 1 + -1 + 1 + 1 + 1 = 3
 * p has sum-k (3-3 = 0). yes
 *   count += p[sum], ie count = p[0] = 2
 * p[2] = 1
 */