/*
  compile time floating point computations may not have the same result as run time. Why? Think about cross compiling.
  During compile time, the build host will have a different FPU and the target host can have some other floating point
  representation.
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[])
{
    constexpr double pi = 3.14876351;
    cout << std::setprecision(10) << pi * 2 << endl;

    double d;
    cin >> d;
    cout << d * 2<< endl;
    return 0;
}

