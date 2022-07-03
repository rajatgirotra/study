// merge sorting

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
using namespace std;

template <typename T>
void merge(T arr[], int p, int q, int r) {
    // Elements arr[p, q] and arr[q+1, r] are already sorted. Need to sort arr[p, r]
    int l_sz = q-p+1;
    int r_sz = r-q;
    T l_arr[l_sz+1] {};
    T r_arr[r_sz+1] {};
    for(int i = 0; i < l_sz; ++i) {
        l_arr[i] = arr[p+i];
    }
    l_arr[l_sz] = std::numeric_limits<T>::max();
    
    for(int i = 0; i < r_sz; ++i) {
        r_arr[i] = arr[q+1+i];
    }
    r_arr[r_sz] = std::numeric_limits<T>::max();

    int i{}, j{};
    for(int k = p; k <=r; ++k) {
        if(l_arr[i] <= r_arr[j]) {
            arr[k] = l_arr[i++];
        } else {
            arr[k] = r_arr[j++];
        }
    }
}

template <typename T>
void merge_sort_helper(T arr[], int p, int r) {
    if(p < r) {
        auto q = (p+r)/2;
        merge_sort_helper(arr, p, q);
        merge_sort_helper(arr, q+1, r);
        merge(arr, p, q, r);
    }
}

template <typename T, int N>
void merge_sort(T (&arr)[N]) {
    merge_sort_helper(arr, 0, N-1);
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
    merge_sort(arr);
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    
}