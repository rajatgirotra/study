/* Egg drop recursive implementation */

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <limits>
#include <algorithm>
using namespace std;

// n eggs and k floors
int32_t eggDrop(int32_t n, int32_t k) {
    // base case
    if (n == 1) {
        return k;
    } else if (k <= 1) {
        return k;
    } else {
        int32_t min = std::numeric_limits<int32_t>::max();
        for (auto x = 1; x <=k; ++x) {
            min = std::min(min, std::max(eggDrop(n-1, x-1), eggDrop(n, k-x)));
        }
        return min + 1;
    }
}

int main(int argc, char* argv[]) {
    int32_t eggs = atoi(argv[1]);
    int32_t floors = atoi(argv[2]);
    cout << "eggDrop(" << eggs << ", " << floors << ") = " << eggDrop(eggs, floors) << endl;
    return 0;
}
