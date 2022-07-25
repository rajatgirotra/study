#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

/* for every element, we will track both the current min and max, as we might have -ive numbers too in the input.*/

int solution(const std::vector<int>& nums) {
    int res = *std::max_element(begin(nums), end(nums));
    int curMax = 1, curMin = 1;

    for(auto&& val : nums) {
        if (val == 0) { 
            // reset curMax, curMin to 1, 1
            curMax = curMin = 1;
            continue;
        }
        int tmpMax = val * curMax;
        curMax = std::max(std::max(val * curMax, val * curMin), val);
        curMin = std::min(std::min(tmpMax, val * curMin), val);
        res = std::max(curMax, res);
    }
    return res;
}

int main() {
   cout << "Max contiguous subarray product (-1, -2, -3, -4): " << solution({-1, -2, -3, -4}) << endl;
   cout << "Max contiguous subarray product (-1, 8): " << solution({-1, 8}) << endl;
   cout << "Max contiguous subarray product (-1, 0): " << solution({-1, 0}) << endl;
}
