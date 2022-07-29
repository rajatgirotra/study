/*
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Basically for every pair of indices you need to do:
   area = std::min(arr[i], arr[j]) * (j-i)
and find the max area.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

// O(n^2)
int maxAreaBruteForce(const vector<int>& height) {
    int maxArea {0};
    for(auto i = 0; i < height.size() - 1; ++i) {
        for(auto j = i+1; j < height.size(); ++j) {
            maxArea = std::max(std::min(height[i], height[j]) * (j-i), maxArea);
        }
    }
    return maxArea;
}

// O(n)
int maxAreaOptimized(const vector<int>& height) {
    int l = 0, r = height.size() - 1;
    int maxArea = 0;
    while (l < r) {
        maxArea = std::max(std::min(height[l], height[r]) * (r-l), maxArea);
        if (height[l] < height[r]) {
            ++l;
        } else {
            --r;
        }
    }
    return maxArea;
}

int main() {
    std::vector<int> heights {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "maxAreaBruteForce: " << maxAreaBruteForce(heights) << endl;
    cout << "maxAreaOptimized: " << maxAreaOptimized(heights) << endl;
}
