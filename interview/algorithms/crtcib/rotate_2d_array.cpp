/*
 * WAP to rotate clockwise a 2D array of integers IN-PLACE.
 *
 * Solution: O(n^2) --> rotate the outer square first. then the internal square and so on.
 */

#include <iostream>
#include <array>
#include <iomanip>
using namespace std;


int main() {
    std::array<std::array<int, 5>, 5> arr {};
    int val{};
    for(auto i = 0; i < arr.size(); ++i) {
        for(auto j = 0; j < arr[i].size(); ++j) {
            arr[i][j] = val++;
        }
    }

    cout << "Original array:\n";
    for(auto i = 0; i < arr.size(); ++i) {
        for(auto j = 0; j < arr[i].size(); ++j) {
           cout << setw(5) << arr[i][j];
        }
        cout << endl;
    }

    // we will have bound of the 2d array, left, right, top, left.
    // in each iteration, we will save the topLeft and replace
    // 1. TopLeft with BottomLeft
    // 2. BottomLeft with BottomRight
    // 3. BottomRight with TopRight
    // 4. TopRight with TopLeft

    int left = 0, right = 4;
    while (left < right) {
	int top = left, bottom = right;
	for (auto i = 0; i < (right - left); ++i) {
	    int topLeft = arr[top][left + i];

	    // replace TopLeft with BottomLeft
	    arr[top][left + i] = arr[bottom - i][left];
	    arr[bottom - i][left] = arr[bottom][right - i];
	    arr[bottom][right -i] = arr[top + i][right];
	    arr[top + i][right] = topLeft;
	}
	++left;
	--right;
    }


    cout << "Rotated array:\n";
    for(auto i = 0; i < arr.size(); ++i) {
        for(auto j = 0; j < arr[i].size(); ++j) {
           cout << setw(5) << arr[i][j];
        }
        cout << endl;
    }
}
