#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;


class Solution {
public:
    int trap(const vector<int>& height) {
        std::vector<int> maxLeft(height.size());
        std::vector<int> maxRight(height.size());
        maxLeft[0] = maxRight[height.size()-1] = 0;
        for(int i = 1u; i < height.size(); ++i) {
            maxLeft[i] = std::max(maxLeft[i-1], height[i-1]);
        }
        for(int i = height.size()-2; i >= 0; --i) {
            maxRight[i] = std::max(maxRight[i+1], height[i+1]);
        }
        auto totalWaterTrapped {0};
        for(int i = 0; i < height.size(); ++i) {
            totalWaterTrapped += std::max(0, std::min(maxRight[i], maxLeft[i]) - height[i]);
        }
        return totalWaterTrapped;
    }
};

int main() {
    Solution sol;
    cout << sol.trap({0,1,0,2,1,0,1,3,2,1,2,1}) << endl;
    cout << sol.trap({4,2,0,3,2,5}) << endl;
}