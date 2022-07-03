// ith order statistic. i.e. the ith smallest element in an unordered sequence.
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

template <typename T, size_t N>
int partition(T (&arr)[N], int p, int r) {
    // i is the index of the last smallest element which is less than pivot.
    // element at index i+1 is greater than pivot and needs to be moved to the right side.
    int pivot = arr[r];
    int i = p-1;
    for(int j = p; j < r; ++j) {
        if(arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[r]);    
    return i+1;
}

template <typename T, size_t N>
int randomized_partition(T (&arr)[N], int p, int r) {
    srand(time(NULL));
    auto rand_idx = (rand() % (r-p+1)) + p;
    std::swap(arr[rand_idx], arr[r]);
    return partition(arr, p, r);
}

template <typename T, size_t N>
int ith_order_statistic(T (&arr)[N], int i, int p = 0, int r = N-1) {
    if (p == r) {
        return arr[p];
    } else {
        auto q = randomized_partition(arr, p, r);
        auto k = q-p+1; // count the number of elements on the lower side + pivot element.
        if(i == k) {
            return arr[q];
        }
        else if (i < k) {
            return ith_order_statistic(arr, i, p, q-1);
        } else {
            return ith_order_statistic(arr,  i-k, q+1, r);
        }
    }
}

int main() {
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-200, 200);
    auto gen = [dist=std::move(dist), engine=std::move(engine)] () mutable  {
        return dist(engine);
    };
    int arr[10] {};
    std::generate(begin(arr), end(arr), gen);

    cout << "Elements\n";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));

    // choose random number between 0 and 10.
    std::uniform_int_distribution<int> dist2(1, 10);
    int i = dist2(engine);
    cout << "\nith order: "<< i << endl;
    cout << "element at ith order: " << ith_order_statistic(arr, i);

    cout << "\nElements sorted\n";
    std::sort(begin(arr), end(arr));
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
}