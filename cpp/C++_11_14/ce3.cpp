#include <iostream>
#include <type_traits>
using namespace std;

struct mystruct {
    static constexpr char whoami[] = "RajatGirotra";
    static_assert(whoami[2] == 'j', "index 2 should be j");

    static constexpr int i {5};
    // Note the important point. No storage declaration needed. You dont need to go the .cpp file and say
    // int mystruct::i = 5;
};

constexpr int half_of(double x) {
    return x / 2;
}

int main() {
    cout << mystruct::i << endl;
    static const int i = 5;
    int arr[i]; // Check with manoj why this is allowed. shouldn't i be constexpr.
    int arr1[half_of(2.0)];   
    return 0;
}
    
