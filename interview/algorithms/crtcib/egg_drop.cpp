/*
Knapsack recursive
*/
#include <iostream>
#include <array>
#include <unordered_map>
#include <limits>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

size_t eggDropRecursive(int eggs, int floors) {
    if(eggs == 1) return floors;
    else if(floors <= 1) return floors;
    else {
        int min_drops = std::numeric_limits<int>::max();
        for(int i = 1; i <= floors; ++i) {
            // doesnt break from floor i
            int valA = eggDropRecursive(eggs, floors-i);
            // breaks from floor i
            int valB = eggDropRecursive(eggs-1, i-1);
            min_drops = std::min(min_drops, std::max(valA, valB));
        }
        return min_drops + 1;
    }
}

size_t eggDropDP(int eggs, int floors) {
    std::vector<std::vector<int>> countArr(eggs+1, std::vector<int>(floors+1));
    for(int i = 0; i <= eggs; ++i) {
        for(int j = 0; j <= floors; ++j) {
            if(i == 0) {
                countArr[i][j] = 0;
            } else if (i == 1) {
                countArr[i][j] = j;
            } else if (j <= 1) {
                countArr[i][j] = j;
            } else {
                countArr[i][j] = std::numeric_limits<int>::max();
                for(int x = 1; x <= j; ++x) {
                    auto res = 1 + std::max(countArr[i-1][x-1], countArr[i][j-x]);
                    countArr[i][j] = std::min(res, countArr[i][j]);
                }
            }
        }
    }


    return countArr[eggs][floors];
}

int main() {
    cout << "Eggdrop(2, 10): " << eggDropRecursive(2, 10) << endl;
    cout << "EggdropDP(2, 10): " << eggDropDP(2, 10) << endl;
}

