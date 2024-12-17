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

// Compare corresponding elements. After each iteration of the outer loop, the largest element is bubbled up to the end.
template <typename T, size_t N>
void bubble_sort(T (&arr)[N]) {
    for(size_t i = 0; i < N - 1; ++i) {
        for (size_t j = 0; j < N-1-i; ++j) {
            if(arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Find the smallest integer in each iteration. Swap it with the element at the beginning of the unsorted part of the array.
template <typename T, size_t N>
void selection_sort(T (&arr)[N]) {
    for(size_t i = 0; i < N - 1; ++i) {
        size_t min_index = i;
        for(size_t j = i+1; j < N; ++j) {
            if(arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        std::swap(arr[i], arr[min_index]);
    }
}

// insertion sort
template <typename T, size_t N>
void insertion_sort(T (&arr)[N]) {
    if(N == 1) return;
    for(int i = 1; i < N; ++i) {
        auto key = arr[i];
        auto j = i-1;
        while(j >=0 && arr[j] > key) {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = key;
    }
}

// quick sort
template <typename T, size_t N>
int randomized_partition(T (&arr)[N], int p, int r) {
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(p, r);
    int i = dist(engine);
    std::swap(arr[i], arr[r]);
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

// quick sort
template <typename T, size_t N>
void quick_sort(T (&arr)[N], int p = 0, int r = N-1) {
    if(p < r) {
        auto q = randomized_partition(arr, p, r);
        quick_sort(arr, p, q-1);
        quick_sort(arr, q+1, r);
    }
}

template <typename T, size_t N>
void merge(T (&arr)[N], int p, int q, int r) {
    // assume arr[p..q] and arr[q+1..r] are sorted
    int l_sz = q - p + 1;
    int r_sz = r - q;
    auto l_arr = std::make_unique_for_overwrite<T[]>(l_sz);
    auto r_arr = std::make_unique_for_overwrite<T[]>(r_sz);
    std::copy_n(std::next(arr, p), l_sz, l_arr.get());
    std::copy_n(std::next(arr, q+1), r_sz, r_arr.get());

    int l_index{0}, r_index{0};
    for(int k = p; k <=r; ++k) {
        if(l_index == l_sz) {
            arr[k] = r_arr[r_index++];
        } else if (r_index == r_sz) {
            arr[k] = l_arr[l_index++];
        } else if(l_arr[l_index] <= r_arr[r_index]) {
            arr[k] = l_arr[l_index++];
        } else {
            arr[k] = r_arr[r_index++];
        }
    }
}

// Find the smallest integer in each iteration. Swap it with the element at the beginning of the unsorted part of the array.
template <typename T, size_t N>
void merge_sort(T (&arr)[N], int p = 0, int r = N-1) {
    if(p < r) {
        auto q = (p+r)/2;
        merge_sort(arr, p, q);
        merge_sort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}

template <typename T, size_t N>
void max_heapify(T (&arr)[N], int i, int heap_size) {
    int l = 2*i +1;
    int r = 2*(i+1);
    int largest = i;
    if(l<heap_size && arr[l] > arr[largest]) {
        largest = l;
    }
    if(r<heap_size && arr[r] > arr[largest]) {
        largest = r;
    }
    if(largest != i) {
        std::swap(arr[largest], arr[i]);
        max_heapify(arr, largest, heap_size);
    }
}

// Ignore the leaves of the heap. For rest of the nodes call max_heapify
template <typename T, size_t N>
void build_max_heap(T (&arr)[N], int heap_size) {
    for(int i = (N/2)+1; i >= 0; --i) {
        max_heapify(arr, i, heap_size);
    }
}

// heap sort
template <typename T, size_t N>
void heap_sort([[maybe_unused]] T (&arr)[N]) {
    auto heap_size = N;
    build_max_heap(arr, heap_size);
    for(int i = N-1; i >= 1; --i) {
        std::swap(arr[0], arr[i]);
        --heap_size;
        max_heapify(arr, 0, heap_size);
    }
}



int main() {
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-100 , 100);

    // random number generator
    auto gen = [&dist, &engine] () mutable { return dist(engine);};

    int arr[15]{};

    // populate array with random numbers
    std::generate(begin(arr), end(arr), gen);
    cout << std::setw(25) << "Input array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));

    // Bubble sort
    std::shuffle(begin(arr), end(arr), engine); // std::random_shuffle is deprecated
    bubble_sort(arr);
    cout << '\n' << std::setw(25) << "Bubble sorted array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));

    // Selection sort
    std::shuffle(begin(arr), end(arr), engine); // std::random_shuffle is deprecated
    selection_sort(arr);
    cout << '\n' << std::setw(25) << "Selection sorted array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));

    // Insertion sort
    std::shuffle(begin(arr), end(arr), engine); // std::random_shuffle is deprecated
    insertion_sort(arr);
    cout << '\n' << std::setw(25) << "Insertion sorted array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));

    // Merge sort
    std::shuffle(begin(arr), end(arr), engine); // std::random_shuffle is deprecated
    merge_sort(arr);
    cout << '\n' << std::setw(25) << "Merge sorted array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));

    // Quick sort
    std::shuffle(begin(arr), end(arr), engine); // std::random_shuffle is deprecated
    quick_sort(arr);
    cout << '\n' << std::setw(25) << "Quick sorted array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));

    // Heap Sort
    std::shuffle(begin(arr), end(arr), engine); // std::random_shuffle is deprecated
    heap_sort(arr);
    cout << '\n' << std::setw(25) << "Heap sorted array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int> (cout, ", "));

}