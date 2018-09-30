#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    auto zeroPointOne = 0.1;
    auto zeroPointTwo = 0.2;
    auto zeroPointThree = 0.3;

    cout << "zeroPointOne: " << std::setprecision(std::numeric_limits<long double>::digits10+1) << zeroPointOne << endl;

    cout << "zeroPointTwo: " << zeroPointTwo << endl;
    cout << "zeroPointThree: " << zeroPointThree << endl;


    cout << "digits (int): " << std::numeric_limits<int>::digits << endl; // 8 * sizeof(int) - 1
    cout << "digits10 (int): " << std::numeric_limits<int>::digits10 << endl;
    cout << "min, max (int): " << std::numeric_limits<int>::min() << "," << std::numeric_limits<int>::max() << endl;
    cout << "radix (int): " << std::numeric_limits<int>::radix << endl;

    cout << "digits (double): " << std::numeric_limits<double>::digits << endl;
    cout << "digits10 (double): " << std::numeric_limits<double>::digits10 << endl;
    cout << "radix (double): " << std::numeric_limits<double>::radix << endl;

    return 0;
}