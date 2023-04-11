#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <cmath>
#include <array>
#include <set>
#include <ostream>
#include <algorithm>
#include <ranges>
using namespace std;

std::uint32_t getPosition(const vector<int>& result, int val) {
    // perform binary search to find the position where argument "val" must go
    // base case for empty list
    if(result.empty()) return 0;
    auto iter = std::lower_bound(begin(result), end(result), val);
    return std::distance(begin(result), iter);
}

std::uint32_t minimumOperations(const vector<int>& numbers) {
    std::vector<int> result{};
    std::uint32_t totalOps{};
    for(auto val : numbers) {
        auto pos = getPosition(result, val);
        // count number of elements before and after
        std::uint32_t leftCount = pos - 0;
        std::uint32_t rightCount = result.size() - pos;
        totalOps += (std::min(leftCount, rightCount) * 2) + 1;
        cout << "position of val: " << val << " is " << pos << endl;
        result.insert(std::next(begin(result), pos), val);
    }
    return totalOps;
}

int main() {
     std::vector<int> arr{10, 6, 2, 3, 7, 1, 2};
//    std::vector<int> arr{10, 15, 20};
    auto res = minimumOperations(arr);
    cout << "Total ops: " << res << endl;

}