/* Given two fractions which are represented as an array of two elements (numerator and denominator),
 * the task is to find the reduced fraction which is the sum of two fractions
 *
 * eg:
 * std::array<int, 2> arr1 {3, 4}; // i.e. 3/4
 * std::array<int, 2> arr2 {4, 5}; // i.e. 4/5
 *
 * 3/4 + 4/5 = (15 + 16)/20 = 31/20 (which is also the simplified form.
 *
 * If either denom is zero, return {0, 0}
 * else do
 * lcm = arr1[1] * arr2[1]
 * num = (arr1[0] * arr2[1]) + (arr2[0] * arr1[1])
 * denom = lcm
 * find gcd of num and denom. report the answer
 */

#include <iostream>
#include <algorithm>
#include <array>
#include <numeric>
#include <cmath>
using namespace std;

constexpr std::array<int, 2> sum_fractions(std::array<int, 2>& arr1, std::array<int, 2>& arr2) {

    auto handle_input_arr = [] (std::array<int, 2>& arr) {
        if(arr[0] * arr[1] < 0) {
            arr[0] = abs(arr[0]) * -1;
        } else {
            arr[0] = abs(arr[0]);
        }
        arr[1] = abs(arr[1]);
    };

    handle_input_arr(arr1);
    handle_input_arr(arr2);

    auto denom = arr1[1] * arr2[1];
    if (denom == 0) {
        return std::array<int, 2>{0, 0};
    } else {
        auto num = (arr1[0] * arr2[1]) + (arr2[0] * arr1[1]);
        int gcd_res = std::gcd(num, denom);
        return std::array<int, 2> {num/gcd_res, denom/gcd_res};
    }
}

int main() {
    std::array<int, 2> arr1{1, 3};
    std::array<int, 2> arr2{-3, 9};

    auto res = sum_fractions(arr1, arr2);

    cout << "(" << arr1[0] << "/" << arr1[1] << ")" << " + "
         << "(" << arr2[0] << "/" << arr2[1] << ")" << " = "
         << "(" << res[0] << "/" << res[1] << ")\n";
}