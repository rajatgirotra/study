/* The order statistic problem is the following: Given a set S of n elements and an integer i, find the i-th smallest element of S.
So if i = 1, then find the smallest element, and if i = n, then find the largest element.

How many comparisons do you need to find the smallest element in an array of n elements? Answer is at least n-1. Similarly,
to find the largest element, you need at least n-1 comparisons. So you need a total of 2n-2 comparisons to find both the smallest and the largest elements.

But can you do better? Yes, instead of doing 2 comparisons for every element separately for finding minimum and maximum, we can do 3 comparisons for every pair of elements.
How? If N is odd, assume 1st element to be both min and max. Then take elements in pair and compare them.
Then compare the min of the pair with the current min and max of the pair with the current max. So you 3 comparisons for every pair of elements. i.e. 3n/2 comparisons.
If N is even, then it will be 3(n-2)/2 + 2 comparisons. So upper bound is 3n/2 (whether N is even or odd).

 For the ith order statistic, we use Randomized select algorithm. Just like randomized partitions in quicksort, we randomly select a pivot element and
partition the array around it.  If we are lucky, we find the ith order statistic in the partitioned array. If not, we recursively call the algorithm on the
 left OR right partition depending on the value of i. The complexity will be O(n) in the average case. O(n2) in the worst case. Worst case is when
 you are unlucky and also partition around the largest element. That is the reason we use randomized partitioning so that randomness will avoid worst case scenario.
 */

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>
#include <array>
#include <iomanip>
#include <memory>
#include <cstring>
#include <cassert>
using namespace std;

template <typename T, size_t N>
int randomized_partition(T (&arr)[N], int p = 0, int r = N-1) {
    // introduce randomness
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(p, r);
    int rand_index = dist(engine);
    std::swap(arr[rand_index], arr[r]);
    auto key = arr[r];

    int q = p-1;
    for(int  j = p; j < r; ++j) {
        if(arr[j] <= key) {
            ++q;
            std::swap(arr[q], arr[j]);
        }
    }
    std::swap(arr[q+1], arr[r]);
    return q+1;
}

// return the index of the i-th order statistic
template <typename T, size_t N>
int randomized_select(T (&arr)[N], int i, int p = 0, int r = N-1) {
    if(p == r) return p;

    auto q = randomized_partition(arr, p, r);
    // number of elements in the left array arr[p..q-1] plus the pivot element
    auto k = q - p + 1;
    if(i == k) return q;
    else if(i < k) return randomized_select(arr, i, p, q-1);
    else return randomized_select(arr, i-k, q+1, r);
}

int main() {
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-100 , 100);

    // random number generator
    auto gen = [&dist, &engine] () { return dist(engine);};

    int arr[15]{};

    // populate array with random numbers
    std::generate(begin(arr), end(arr), gen);
    cout << std::setw(30) << "Input array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));

    // get a random index
    std::uniform_int_distribution<int> dist_index(1, 15);
    int i = dist_index(engine);

    // randomized select
    auto res = randomized_select(arr, i);
    cout << endl;
    cout << std::setw(30) << "i_th order statistic (i: "<< i << "): " << arr[res] << endl;

    cout << std::setw(30) << "Sorted array: ";
    std::sort(begin(arr), end(arr));
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));
}