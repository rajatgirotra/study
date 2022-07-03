// counting sorting. Linear order sorting used to sort elements n elements all 
// of which are in the range 0..k
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

template <size_t N>
void counting_sort(int (&arr)[N], int k) {
    // first create an array of size k+1
    int c[k+1] {};

    // count how many times each element occurs in the input arr
    for (int elem : arr) {
        ++c[elem];
    }

    // count the number of elements equal or less than the current element
    for (int idx = 1; idx <= k; ++idx) {
        c[idx] += c[idx-1];
    }

    // make a copy of the input array and then modify it.
    int arr_copy[N] {};
    std::copy(begin(arr), end(arr), begin(arr_copy));
    for(int elem : arr_copy) {
        arr[c[elem]-1] = elem;
        --c[elem];
    }
}

int main() {
    // n = 10
    // k = 0..15, so fill arr with random elements between 0 and 15 (both inclusive)
    int arr[10] {};

    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(0, 15);
    auto gen = [dist = dist, engine = engine] () mutable {
        return dist(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    cout << "Elements before\n";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    counting_sort(arr, 15);
    cout << "\nElements sorted\n";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;
}