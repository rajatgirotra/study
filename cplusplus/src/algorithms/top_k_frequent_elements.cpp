

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> result{};
        std::unordered_map<int, int> itemCountMap{}; // map of elements and their frequeny count.
        for(auto item : nums) {
            ++itemCountMap[item];
        }

        std::vector<std::vector<int>> frequencies{nums.size()+1, std::vector<int>()};
        for(auto [x, y] : itemCountMap) {
            frequencies[y].emplace_back(x);
        }

        for(int i = nums.size(); i >= 0 && k > 0; --i) {
            if(!frequencies[i].empty()) {
                std::copy(frequencies[i].begin(), frequencies[i].end(), std::back_inserter(result));
                k -= frequencies[i].size();
            }
        }
        return result;
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

    std::vector<int> v1{1,1,1,2,2,3};
    cout << "1st example: " << s.topKFrequent(v1, 2) << endl;

    std::vector<int> v2{1,1};
    cout << "2nd example: " << s.topKFrequent(v2, 1) << endl;

    std::vector<int> v3{4,1,-1,2,-1,2,3};
    cout << "3rd example: " << s.topKFrequent(v3, 2) << endl;
}