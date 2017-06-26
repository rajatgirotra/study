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

// Also called Kadane's algorithm
int32_t lcs_linear_dp() {
    int32_t runningSum = arr[0];
    int32_t maxSum = arr[0];
    for(int i = 1; i < arr.size(); ++i) {
        runningSum = std::max(runningSum + arr[i], arr[i]);
        maxSum = std::max(runningSum, maxSum);
    }
    return maxSum;
}


int main() {
    cout << "lcs_brute_on3 = " << lcs_brute_on3() << endl;
    cout << "lcs_brute_on2 = " << lcs_brute_on2() << endl;
    cout << "lcs_linear_dp = " << lcs_linear_dp() << endl;
    return 0;
}
