#include "practice_jul2021.hpp"
#include <type_traits>
#include <iostream>
using namespace std;

[[maybe_unused]] const int* p = &mystruct::m_value;
//constexpr int mystruct::m_value {99};

const char* pi_function(int index) {
    static constexpr char name[] {"Rajat"};
    return (name + index);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    constexpr int constexpr_3 = 3;
    const int const_3 = 3;
    static_assert(constexpr_3 == const_3, "integral constexpr_3 == const_3");
    [[maybe_unused]] char char_array1[constexpr_3] {};
    [[maybe_unused]] char char_array2[const_3] {};

    [[maybe_unused]] constexpr double constexpr_half = 0.5;
    [[maybe_unused]] const double const_one_half = 1.5; // only integral constexpr values are really constant at compile time.
//    static_assert(constexpr_half < const_one_half); // this line will fail to compile. So you see a difference between const and constexpr

    constexpr char name[] = "Rajat";
    static_assert(name[2] == 'j', "index 2 must be j!");

    cout << *(pi_function(2));
}
