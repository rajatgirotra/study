#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

/* for every element, we will track both the current min and max, as we might have -ive numbers too in the input.*/

int solution(const std::vector<int>& nums) {
    auto res = *std::max_element(begin(nums), end(nums));
    auto currMax = 1, currMin = 1;
    for(auto&& val : nums) {
        if(val == 0) {
            currMax = currMin = 1;
            continue;
        }
        auto tmpMax = val * currMax;
        currMax = std::max(std::max(val * currMax, val*currMin), val);
        currMin = std::min(std::min(tmpMax, val*currMin), val);
        res = std::max(res, currMax);
    }
    return res;
}

int main() {
    cout << "Max contiguous subarray product (-1, -2, -3, -4): " << solution({-1, -2, -3, -4}) << endl;
    cout << "Max contiguous subarray product (-1, 8): " << solution({-1, 8}) << endl;
    cout << "Max contiguous subarray product (-1, 0): " << solution({-1, 0}) << endl;
}
