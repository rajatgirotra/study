/*
* WAP to rotate clockwise a 2D array of integers IN-PLACE.
*
* Solution: O(n^2) --> rotate the outer square first. then the internal square and so on.
*/

#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

template <size_t N>
void rotate_2d_array(std::array<std::array<int, N>, N>& arr) {
    auto left = 0;
    auto right = N-1;
    while(left < right) {
        auto top = left;
        auto bottom = right;
        for(auto i = 0; i < right-left; ++i) {
            auto topLeft = arr[top][left + i];

            arr[top][left + i] = arr[bottom - i][left];

            arr[bottom - i][left] = arr[bottom][right - i];

            arr[bottom][right - i] = arr[top + i][right];

            arr[top + i][right] = topLeft;
        }
        ++left;
        --right;
    }
}

int main() {
    std::array<std::array<int, 5>, 5> arr{};
    int val{};
    for (auto i = 0; i < arr.size(); ++i) {
        for (auto j = 0; j < arr[i].size(); ++j) {
            arr[i][j] = val++;
        }
    }

    cout << "Original array:\n";
    for (auto i = 0; i < arr.size(); ++i) {
        for (auto j = 0; j < arr[i].size(); ++j) {
            cout << setw(5) << arr[i][j];
        }
        cout << endl;
    }

    rotate_2d_array(arr);

    cout << "Rotated array:\n";
    for (auto i = 0; i < arr.size(); ++i) {
        for (auto j = 0; j < arr[i].size(); ++j) {
            cout << setw(5) << arr[i][j];
        }
        cout << endl;
    }
}