/*
Given an array of integers, write a program to move all zero's to the right while maintaining the order.
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <array>
using namespace std;

template <size_t N>
void move_zeros(std::array<int, N>& arr) {
    // do like we do quick partition in quick sort. 
    // whenever you find a non zero element, bring it forward. After one iteration, all zeros 
    // will be at the end.
    int j = -1;
    for(int i = 0; i < N; ++i) {
        if(arr[i] != 0) {
            ++j;
            std::swap(arr[i], arr[j]);
        }
    }
}

int main() {
    std::array<int, 6> arr{};

    std::random_device r;
    std::default_random_engine engine(r());

    // lets create an array of 0 and 1's only. then we will scale the 1's to some higher number.
    // this will we will have more than one zeros likely in the input array
    std::uniform_int_distribution dist(0, 1);
    auto gen = [dist = std::move(dist), engine = engine]  () mutable {
        return dist(engine);
    };

    std::generate(begin(arr), end(arr), gen);
    std::transform(begin(arr), end(arr), begin(arr), [](const int& value) {
        std::random_device r;
        std::default_random_engine engine(r());
        std::uniform_int_distribution dist(2, 10);
        return value * dist(engine);
    });

    cout << "Array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
    move_zeros(arr);
    cout << "\nArray after moving zeros: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
    cout << endl;
}