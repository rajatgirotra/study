// heap sorting

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
using namespace std;

#define LEFT(x) (2*x + 1)
#define RIGHT(x) (2*x + 2)
#define PARENT(x) ((x-1)/2)

int HEAP_SIZE{};

template <typename T>
void max_heapify(T arr[], size_t index) {
    size_t l_idx = LEFT(index);
    size_t r_idx = RIGHT(index);
    size_t largest_idx = index;
    if(l_idx < HEAP_SIZE && arr[index] < arr[l_idx]) {
        largest_idx = l_idx;
    }
    if (r_idx < HEAP_SIZE && arr[largest_idx] < arr[r_idx]) {
        largest_idx = r_idx;
    }

    if(index != largest_idx) {
        std::swap(arr[index], arr[largest_idx]);
        max_heapify(arr, largest_idx);
    }
}

template <typename T, size_t N>
void build_max_heap(T (&arr)[N]) {
    HEAP_SIZE = N;
    for(int i = N/2 - 1; i >=0; --i) {
        max_heapify(arr, i);
    }    
}

template <typename T, size_t N>
void heap_sort(T (&arr)[N]) {
    build_max_heap(arr);
    for(int i = N-1; i >= 1; --i) {
        std::swap(arr[0], arr[i]);
        --HEAP_SIZE;
        max_heapify(arr, 0);
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
    heap_sort(arr);
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    
}