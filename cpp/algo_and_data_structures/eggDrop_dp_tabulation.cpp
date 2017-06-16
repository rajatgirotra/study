/* Egg drop recursive implementation */

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <limits>
#include <algorithm>
using namespace std;

// n eggs and k floors
int32_t eggDrop(int32_t n, int32_t k) {
    int32_t table[n+1][k+1] = { {0} };
    for (auto i = 1; i <=n; ++i) {
        for (auto j = 1; j <=k; ++j) {
            table[i][j] = std::numeric_limits<int32_t>::max();
            for(auto x = 1; x<=j; ++x) {
                if (i == 1)
                    table[i][j] = j;
                else if (j <=1 )
                    table[i][j] = j;
                else
                    table[i][j] = std::min(table[i][j], 1 + std::max(table[i-1][x-1], table[i][j-x]));
            }
        }
    }
    return table[n][k];
}

int main(int argc, char* argv[]) {
    int32_t eggs = atoi(argv[1]);
    int32_t floors = atoi(argv[2]);
    cout << "eggDrop(" << eggs << ", " << floors << ") = " << eggDrop(eggs, floors) << endl;
    return 0;
}
