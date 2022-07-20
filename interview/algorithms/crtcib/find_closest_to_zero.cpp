/*
Given an integer array (one element is input at one time using cin).
Find the element which is closest to zero. (out of -2 and 3, -2 is closer, out of -2 and 2, 2 is closer).
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int n;
    cin >> n; cin.ignore();

    int closest = std::numeric_limits<int>::max();
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t; cin.ignore();
        if(closest + t == 0) {
            closest = std::max(closest, t);
        } else {
            closest = (abs(closest) < abs(t) ? closest : t);
        }
    }

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    if (closest == std::numeric_limits<int>::max()) {
        cout << "0" << endl;
    } else {
        cout << closest << endl;
    }
    
}
