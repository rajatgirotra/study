#include <iostream>
#include <type_traits>

using namespace std;

template <auto x>
struct S {};

int main() {
    S<5> s;
    cout << std::boolalpha;
    cout << std::is_same<decltype(s), S<int>>::value << endl;
    return 0;
}
