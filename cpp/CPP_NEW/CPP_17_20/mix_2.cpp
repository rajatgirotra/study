#include <iostream>
using namespace std;

template <typename T>
void lineInfo(const T& t) {
//void lineInfo(T&& t) { // think why the output changes with this simple change. Then you will remember to use std::remove_reference
    using WithoutRef_t = T; // std::remove_reference_t<T>;
    if constexpr (std::is_integral_v<WithoutRef_t>) {
            cout << "num: " << t << "\n";
    }
    else if constexpr (std::is_floating_point_v<WithoutRef_t>) {
        const auto frac = t - static_cast<float>(static_cast<long>(t));
        cout << "flt: " << t <<", fraction: " << frac << "\n";
    } else if constexpr (std::is_pointer_v<WithoutRef_t>) {
        cout << "ptr, ";
        lineInfo(*t);
    } else {
        cout << "string: " << t << "\n";
    }
}

template <typename... Args>
void printLineInfo(Args... args) {
    // fold expression over the comma operator
    (lineInfo(args), ...);
}

int main()
{
    int i = -99;
    float flt = -0.33f;
    string s("Hello World");
    printLineInfo(&i, &flt, s);
}