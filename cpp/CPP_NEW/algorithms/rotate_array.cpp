/*
rotate an element of integers by a given number k. if k is -ive, rotate left, if k is +ive, rotate right.
abs(k) may be greater than input array size n.

Simple solution: O(n) space, O(n), copy the array first and then copy the elements rotated.
*/

#include <array>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cmath>
#include <cassert>
#include <random>
#include <charconv>
#include <cstring>
using namespace std;

template <size_t N>
void rotate_right_trivial(std::array<int, N>& arr, int rotate_by) {
    std::array<int, N> tmp(arr);
    for(auto i = 0; i < arr.size(); ++i) {
        arr[(i + rotate_by)%arr.size()] = tmp[i];
    }
}

template <size_t N>
void reverse(std::array<int, N>& arr, int l, int r) {
    while(l < r) {
        std::swap(arr[l], arr[r]);
        ++l;
        --r;
    }
}

template <size_t N>
void rotate_right_On_space(std::array<int, N>& arr, int rotate_by) {
    // reverse the complete array first and then reverse the individual halves.
    reverse(arr, 0, N-1);
    reverse(arr, 0, rotate_by-1);
    reverse(arr, rotate_by, N-1);
}

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Usage\n\t" << argv[0] << " <rotate_by>\n";
        return -1;
    }
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-10, 10);

    auto gen = [&dist, &engine] () {
        return dist(engine);
    };

    std::array<int, 12> arr{};
    std::generate(begin(arr), end(arr), gen);

    cout << "Array: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;

    int k{};
    auto [ptr, ec] = std::from_chars(argv[1], argv[1] + strlen(argv[1]), k, 10);
    if(ec == std::errc()) {
        cout << "Rotate by " << k << endl;
        k %= static_cast<int>(arr.size()); // very important
        cout << "Rotate by effective " << k << endl;
        if(k < 0) {
            k = (static_cast<int>(arr.size()) - abs(k));
        }
        cout << "Rotate right by effective " << k << endl;
        rotate_right_trivial(arr, k);
//        rotate_right_On_space(arr, k);
        cout << "Rotated Array: ";
        std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
        cout << endl;
    } else {
        cout << "Invalid input " << argv[1] << endl;
    }
}