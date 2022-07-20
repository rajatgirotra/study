/*
rotate an element of integers by a given number k. if k is -ive, rotate left, if k is +ive, rotate right.
abs(k) may be greater than input array size n.

Simple solution: O(n) space, O(n), copy the array first and then copy the elements rotated.
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <array>
#include <cmath>
using namespace std;

template <size_t N>
void rotate_extra_space(std::array<int, N>& arr, int k) {
    std::array<int, N> arr_copy {arr};
    auto rotate_idx = k;
    for(auto idx = 0; idx < N; ++idx) {
        arr[rotate_idx] = arr_copy[idx];
        rotate_idx = (rotate_idx + 1) % N;
    }
}

void reverse(int* arr, int l, int r) {
    while(l < r) {
        std::swap(arr[l], arr[r]);
        ++l;
        --r;
    }
}

template <size_t N>
void rotate_no_extra_space(std::array<int, N>& arr, int k) {
    reverse(arr.data(), 0, N-1); // first reverse full array
    reverse(arr.data(), 0, k-1); // then reverse the two halves
    reverse(arr.data(), k, N-1);
}

int main() {
    std::array<int, 10> arr { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int rotate_by = -7;
    rotate_by %= static_cast<int>(arr.size());
    if(rotate_by < 0) {
        rotate_by += arr.size();
    }

    // now we need to rotate right only.
    cout << "Input array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
    cout << endl;
    cout << "Rotate_by: " << rotate_by << endl;
    // rotate_extra_space(arr, rotate_by);
    rotate_no_extra_space(arr, rotate_by);
    cout << "rotated array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
}