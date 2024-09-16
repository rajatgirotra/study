/*
 * Given an unsorted array of integers, find two numbers such that they add up to a specific target number.
 * Brute force is O(n₂). i.e. for each element, we scan the rest of the array to find the other element.
 *
 * Better solution is O(n) time and space complexity using a HashMap. Very trivial to implement.
 */

#include <unordered_map>
#include <vector>
#include <iostream>
#include <random>
#include <array>
#include <algorithm>
#include <iterator>

using namespace std;

std::pair<int, int> two_sum_unsorted(const std::array<int, 10>& arr, int target) {
    std::unordered_map<int, int> m;
    for(auto i = 0; i < arr.size(); ++i) {
        auto subSum = target - arr[i];
        auto iter = m.find(subSum);
        if(iter != m.end()) {
            return {iter->second, i};
        }
        m[arr[i]] = i;
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

    // get two random indices and get the sum of the elements at those indices
    std::uniform_int_distribution<int> dist_index(0, arr.size()-1);
    auto gen_index = [&dist_index, &engine] () { return dist_index(engine);};
    auto i = gen_index();
    auto j = gen_index();
    auto target = arr[i] + arr[j];

    auto [a, b] = two_sum_unsorted(arr, target);

    cout << "Array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));
    cout << "\nTarget: " << target << "\n";
    cout << "two_sum_unsorted(arr, target) returned indices = " << a << ", " << b << "\n";
}