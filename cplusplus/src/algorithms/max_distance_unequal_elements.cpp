/*
given a vector of integers. how can I found the max difference between two indices where the values are unequal?
 */

#include <array>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <random>
#include <vector>
using namespace std;

// very trivial. Calculate maximum distance of left element from arr[N-1].
// Calculate maximum distance of right element from arr[0]. return maximum of both

int maxDistance(const std::vector<int>& nums) {
    if (nums.size() < 2) return 0;

    int left = 0, right = nums.size() - 1;

    while (left < right && nums[left] == nums[right]) {
        ++left;
    }

    while (left < right && nums[0] == nums[right]) {
        --right;
    }

    int N = nums.size();
    return std::max(right, N-1-left);

}

int main() {
    // std::vector<int> arr{1, 2, 1, 3, 4, 2, 3};
    std::vector<int> arr{5, 5, 5, 1, 5};

    cout << maxDistance(arr) << endl;
    return 0;
}