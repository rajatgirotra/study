// Bubble sorting

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;

template <typename T, size_t N>
void bubble_sort(T (&arr)[N]) {
    for(int i = 0; i < N-1; ++i) {
        for(int j = 0; j < N-2-i; ++j) {
            if(arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
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

    cout << "Elements before\n";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));

    cout << "\n\nElements after\n";
    bubble_sort(arr);
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    
}