/*
Maximum contiguous subarray: Given an input array of intergers.
find a subarray (with atleast one element) which has the maximum sum.

Brute force will be O(n^3) and with little optimization can be O(n^2).
But below is a O(n) solution, where we maintain a curSum as we traverse the array.
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
#include <cstring>
#include <utility>
#include <ctime>
using namespace std;

template<size_t N>
void maximum_contiguous_subarray_sum(int (&arr)[N]) {
    int maxSum = arr[0], runningSum = arr[0];
    for(int i = 1; i < N; ++i) {
        runningSum += arr[i];
        runningSum = std::max(runningSum, arr[i]);
        maxSum = std::max(maxSum, runningSum);
    }
    cout << "Max contiguous subarray sum: " << maxSum << endl;
}


int main() {
    int arr[8] {};
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-4, 4);
    auto gen = [dist = dist, engine = engine] () mutable {
        return dist(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    cout << "Elements: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;

    maximum_contiguous_subarray_sum(arr);
    //    int x[]{-4, 2, -4, 2, 4, -2, -2, -3 };
    //    int x[] {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    //    maximum_contiguous_subarray_sum(x);
}
