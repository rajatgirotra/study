// quicksort (randomized version)
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
void quick_sort(T (&arr)[N], int p = 0, int r = N-1) {
    if (p < r) {
        auto q = randomized_partition(arr, p, r);
        quick_sort(arr, p, q-1);
        quick_sort(arr, q+1, r);
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

    cout << "Elements before\n";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));

    cout << "\n\nElements after\n";
    quick_sort(arr);
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    
}