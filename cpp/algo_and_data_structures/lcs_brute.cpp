#include <iostream>
#include <cstdint>
#include <array>
using namespace std;

constexpr std::array<int32_t, 8> arr {-2, -3, 4, -1, -2, 1, 5, -3};

int32_t lcs_brute_on3() {
    int32_t lcs = arr[0];
    for(int i = 0; i < arr.size(); ++i) {
        for(int j = i; j < arr.size(); ++j) {
                int32_t sum = 0;
            for (int k = i; k < j; ++k) {
                sum += arr[k];
                if (sum > lcs)
                    lcs = sum;
            }
        }
    }
    return lcs;
}


int32_t lcs_brute_on2() {
    int32_t lcs = arr[0];
    for(int i = 0; i < arr.size(); ++i) {
            int32_t sum = 0;
        for(int j = i; j < arr.size(); ++j) {
            sum += arr[j];
            if (sum > lcs)
                lcs = sum;
        }
    }
    return lcs;
}


int main() {
    cout << "lcs = " << lcs_brute_on3() << endl;
    cout << "lcs = " << lcs_brute_on2() << endl;
    return 0;
}
