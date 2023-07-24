/*
 * There is an integer array nums sorted in ascending order (with distinct values).
 * Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such
 * that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
 * For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
 * Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
 * You must write an algorithm with O(log n) runtime complexity.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <array>
#include <random>
#include <iterator>
using namespace std;

int search_in_sorted_rotated_arr(const std::vector<int>& arr, int elem) {
    auto left = 0;
    auto right = static_cast<int>(arr.size()-1);
    while(left <= right) {
        auto mid = (left+right)/2;
        // did we find the elem
        if(arr[mid] == elem) {
            return mid;
        }
        if (arr[left] <= arr[mid]) {
            // we are in left array
            if(arr[mid] < elem || elem < arr[left]) {
                left = mid+1;
            } else {
                right = mid-1;
            }
        } else {
            // we are in right array
            if(elem < arr[mid] || elem > arr[right]) {
                right = mid-1;
            } else {
                left = mid+1;
            }
        }
    }
    return -1;
}

int main() {
    std::vector<int> arr(8);
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(0, 10);

    auto gen = [&dist, &engine] () {
        return dist(engine);
    };

    // generate random values.
    std::generate(begin(arr), end(arr), gen);

    // sort it
    std::sort(begin(arr), end(arr));

    //rotate it
    std::uniform_int_distribution<int> dist2(0, 8);
    std::rotate(begin(arr), std::next(begin(arr), dist2(engine)), end(arr));

    // print rotated array
    cout << "Input array\n";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;

    auto elem = dist(engine);
    cout << "Element to search: " << elem << endl;
    cout << "Index of element " << elem << ": " << search_in_sorted_rotated_arr(arr, elem) << endl;
}