#include <iostream>
#include <string>
#include <limits>
#include <cmath>
using namespace std;

double mysqrt(double arg) {
    double lb = 1., ub = arg;
    double epsilon = 0.000001;
    while (std::fabs(lb-ub) > epsilon) {
        auto mid = (lb+ub)/2;
        auto mid_square = mid * mid;
        if (mid_square > arg) {
            ub = mid;
        } else if (mid_square < arg) {
            lb = mid;
        } else {
            return mid;
        }
    }
    return lb;
}

int main() {
    cout << mysqrt(42) << endl;
}
