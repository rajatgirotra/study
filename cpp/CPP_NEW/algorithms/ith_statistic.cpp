#include <array>
#include <iostream>
#include <iterator>
#include <random>
#include <algorithm>
#include <cassert>
using namespace std;

template <size_t N>
int randomized_partition(std::array<int, N>& arr, int p, int r) {
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(p, r);
    auto index = dist(engine);
    std::swap(arr[index], arr[r]);
    int pivot = arr[r];
    int j = p-1;
    for(int i = p; i < r-1; ++i) {
        if(arr[i] < pivot) {
            ++j;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[j+1], arr[r]);
    return j+1;
}


template <size_t N>
int ith_statistic_impl(std::array<int, N>& arr, int p, int r, int i) {
    if(p == r) {
        return arr[p];
    } else {
        int q = randomized_partition(arr, p, r);
        int k = q - p + 1;
        if(i == k) return arr[q];
        else if (i < k) {
            return ith_statistic_impl(arr, p, q-1, i);
        } else {
            return ith_statistic_impl(arr, q+1, r, i-k);
        }
    }
}

template <size_t N>
int ith_statistic(std::array<int, N>& arr, int i) {
    assert(i >= 0 && i <= N);

    return ith_statistic_impl(arr, 0, N-1, i);
}

int main() {
    std::random_device r;
    std::default_random_engine engine(r());

    std::uniform_int_distribution<int> dist(-8, 8);

    [[maybe_unused]] auto gen = [&dist, &engine] () {
        return dist(engine);
    };

//    std::array<int, 8> arr{-3, 0, 8, 9, 6, 2, 4, -4 };
    std::array<int, 8> arr{4, 8, 6, -1, 1, -8, 2, -7};
//    std::generate(begin(arr), end(arr), gen);
    cout << "Input array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, " "));
    cout << endl;

    int res = ith_statistic(arr, 2);
    cout << "2nd smallest element: " << res;
}