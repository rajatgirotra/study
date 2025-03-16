/*
You are given a 0-indexed array nums of size n consisting of non-negative integers.

You need to apply n - 1 operations to this array where, in the ith operation (0-indexed), you will apply the following on the ith element of nums:

If nums[i] == nums[i + 1], then multiply nums[i] by 2 and set nums[i + 1] to 0. Otherwise, you skip this operation.
After performing all the operations, shift all the 0's to the end of the array.

For example, the array [1,0,2,0,0,1] after shifting all its 0's to the end, is [1,2,1,0,0,0].
Return the resulting array.

Note that the operations are applied sequentially, not all at once.
 */

#include <array>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <random>
#include <vector>
using namespace std;

auto applyOperations(vector<int>& arr) -> vector<int> {
    for (int  i = 0; i < arr.size()-1; ++i) {
        if (arr[i] == arr[i+1]) {
            arr[i] *= 2;
            arr[i+1] = 0;
        }
    }

    int j = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] != 0) {
            std::swap(arr[i], arr[j]);
            ++j;
        }
    }
    return arr;
}

int main() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(0, 4);

    auto gen = [&]() { return dist(engine); };

    std::vector<int> arr(9, 0);
    for (int i = 0; i < arr.size(); ++i) {
        std::generate(begin(arr), end(arr), gen);
    }

    cout << "Input: ";
    std::copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    auto res = applyOperations(arr);
    cout << "Output: ";
    std::copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
}
