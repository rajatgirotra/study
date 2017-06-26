#include <iostream>
#include <vector>
#include <tuple>
#include <cstdint>
#include <unordered_map>
#include <algorithm>
using namespace std;

using Int_2_tuple = std::tuple<int32_t, int32_t>;

// Brute force O(n2) time complexity, O(1) space complexity.
// For every pair, check if it adds to given sum 
#if 0
Int_2_tuple twoSum(const vector<int32_t> array, int32_t sum) {
    for(auto i1 = 0; i1 < array.size()-1; i1++) {
        for (auto i2 = i1+1; i2 < array.size(); i2++) {
            if (array[i1] + array[i2] == sum)
                return std::make_tuple(i1, i2);
        }
    }
    return std::make_tuple(-1, -1);
}
#endif

// O(n) time, O(n) space using hash table.
// Iterate through each element and insert in a hash table.
// Iterate again and subtract each element from the given sum. Then lookup the difference in the hash table. 
// index 1 should always be less than index 2.
#if 0
Int_2_tuple twoSum(const vector<int32_t> array, int32_t sum) {
    std::unordered_map<int32_t, int32_t> m; // map of <element, element_index>
    int index{};
    for(const auto& i : array) {
        m.insert(std::make_pair(i, index));
        ++index;
    }

    for(const auto& item : m) {
        const auto& iter = m.find(sum-item.first);
        // compare second also, so that you don't consider the same elements during checking.
        if (iter != m.end() && iter->second != item.second) {
            return std::make_tuple(std::min(item.second, iter->second),
                                   std::max(item.second, iter->second));
        }
    }
    return std::make_tuple(-1, -1);
}
#endif

// If array is sorted already.
// O(nlg n) running time, O(1) space: For every element, do a binary search for (sum-element_value)
#if 0
Int_2_tuple twoSum(const vector<int32_t> array, int32_t sum) {
    for(auto iter = array.begin(); iter != array.end()-1; ++iter) {
       const auto& found_iter = std::lower_bound(iter+1, array.end(), sum-*iter); 
       if (found_iter != array.end()) {
           return std::make_tuple(iter-array.begin(), found_iter-array.begin());
       }
    } 
    return std::make_tuple(-1, -1);
}
#endif

// O(n) time, O(1) space. Start a loop with one position at the start, one position at the end.
// if start+end > sum, reduce end
// if start+end < sum, increment start
// else return indices as this is a match
#if 1
Int_2_tuple twoSum(const vector<int32_t> array, int32_t sum) {
    for(int start = 0, end = array.size()-1; start < end;) {
        auto tmpSum = array[start] + array[end];
        if (tmpSum > sum)
            --end;
        else if (tmpSum < sum)
            ++start;
        else
            return std::make_tuple(start, end); 
    }
    return std::make_tuple(-1, -1);
}
#endif

int main() {
    std::vector<int32_t> v {10, 20, 30, 40, 50};
    int32_t a, b;
    std::tie(a, b) = twoSum(v, 100);
    cout << "index 1: " << a << "     index 2: " << b << endl;
    return 0;
}
