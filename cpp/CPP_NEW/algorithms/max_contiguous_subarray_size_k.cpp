/* find the maximum contiguous subarray of size k in an array of size n
   very trivial. compute the maximum of all possible subarray's of size k. and maintain a maximum. It will take O(n.k)

   better way: compute arr[0] + arr[1] + arr[2] +.. + arr[k].
   then for each index i from k to n, adjust the sum by adding arr[i] and subtracting arr[i-k]
*/

#include <iostream>
#include <array>
#include <random>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <utility>
#include <iterator>
using namespace std;

template <auto N>
auto max_contiguous_subarr_k(std::array<int, N> arr, int k) {
}

int main() {

    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution dist(-9, 9);
    std::array<int, 8> arr;

    auto gen = [&]() {
        return dist(engine);
    };

    std::generate(begin(arr), end(arr), gen);

    cout <<"Input array: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;

    int k = 4;

    auto res = max_contiguous_subarr_k(arr, k);
    cout << "max_sum is from index " << res.first << " to " << res.second << ": " << std::accumulate(begin(arr)+res.first, begin(arr)+res.first+k, 0) << endl;
}
