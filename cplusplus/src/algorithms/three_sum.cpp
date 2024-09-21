/*
 * Given an unsorted array of integers (-ive and +ive numbers), find three numbers that sum to 0.
 * Find all such triplets. But do not return duplicates.
 *
 * Brute force: For every element, call two_sum_unsorted on the rest of the array.
 * Example: if element is 7, find two sum on the rest of the array with target as -7.
 *
 * This will be O(n²) time complexity; assuming O(n) complexity for two_sum_unsorted.
 * But problem with this approach is that it will return duplicates also.
 *
 * Another solution is to sort the array and then use the left and right pointer approach.
 * Sorting will be O(n lg n) and then for each element, we will use left and right pointers to find the other two elements.
 * So overall will be O(n lg n) + O(n) = O(n lg n).
 *
 */

#include <unordered_map>
#include <vector>
#include <ranges>
#include <iostream>
#include <random>
#include <array>
#include <algorithm>
#include <iterator>

using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

// can you simplify this function?
template <size_t N>
std::vector<std::array<int, 3>> three_sum(std::array<int, N>& arr) {
    std::vector<std::array<int, 3>> res;
    rng::sort(arr);

    for(size_t i = 0; i < N-2; ++i) {
        if(i > 0 && arr[i] == arr[i-1]) continue;
        size_t l{i+1}, r{N-1};
        while(l < r) {
            auto sum = arr[i] + arr[l] + arr[r];
            if(sum == 0) {
                res.emplace_back(std::array<int, 3>{arr[i], arr[l], arr[r]});
                ++l;
                while(l < r && arr[l] == arr[l-1]) {
                    ++l;
                }
            } else {
                sum < 0 ? ++l : --r;
            }
        }
    }
    return res;
}

int main() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(-10, 10);
    auto gen = [&dist, &engine] () { return dist(engine);};
    std::array<int, 12> arr;
    std::generate(begin(arr), end(arr), gen);

    auto res = three_sum(arr);

    cout << "Array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));
    cout << "\nTriplets that sum to 0 are:\n";
    for(auto[a, b, c] : res) {
        cout << a << ", " << b << ", " << c << "\n";
    }
}