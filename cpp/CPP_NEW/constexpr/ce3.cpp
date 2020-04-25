#include <iostream>
#include <type_traits>
using namespace std;

struct mystruct {
    static constexpr char whoami[] {"RajatGirotra"};
    static_assert(whoami[2] == 'j', "index 2 should be j");

    //static constexpr int i {5};
    static const int i {5};
    // Note the important point. No storage declaration needed. You dont need to go the .cpp file and say
    // int mystruct::i = 5; Is this really due to constexpr. If we are assigning 5 explicitly in the declaration, why should we need to go to .cpp anyway?
    // this requirement is relaxed only as of C++17. For C++14 and earlier, you still need to provide an out of class definition for your static member variable.
};

constexpr int half_of(double x) noexcept {
    return x / 2;
}

int main() {
    cout << mystruct::i << endl;
    static const int i = 5;
    static_assert(i==5, "i is not 5");
    /*
     * this will fail in C89 standard, as VLA (Variable length arrays were not legal in C89). However gcc allowed it as an extension.
     * C99 added support for VLA's. C++11 made it optional, so compilers may/may not support it. You can check the
     * __STDC_NO_VLA__ to check if VLA's are supported or not.
     */
    int arr[i];
    int arr1[half_of(2.0)];
    return 0;
}
    
