/*
 * Same as two_sum_unsorted.cpp but the array is sorted.
 * Can be easily done using left and right pointers.
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

std::pair<int, int> two_sum_sorted(const std::array<int, 10>& arr, int target) {
    size_t l{}, r{arr.size()-1};
    while(l < r) {
        if(arr[l] + arr[r] == target) {
            return {l, r};
        } else if(arr[l] + arr[r] < target) {
            l++;
        } else {
            r--;
        }
    }
    return {-1, -1};
}

int main() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(0, 100);
    auto gen = [&dist, &engine] () { return dist(engine);};
    std::array<int, 10> arr;
    std::generate(begin(arr), end(arr), gen);
    rng::sort(arr);

    // get two random indices and get the sum of the elements at those indices
    std::uniform_int_distribution<int> dist_index(0, arr.size()-1);

    auto gen_index = [&dist_index, &engine] () { return dist_index(engine);};
    auto i = gen_index();
    auto j = gen_index();
    auto target = arr[i] + arr[j];

    auto [a, b] = two_sum_sorted(arr, target);

    cout << "Array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));
    cout << "\nTarget: " << target << "\n";
    cout << "two_sum_sorted(arr, target) returned indices = " << a << ", " << b << "\n";
}