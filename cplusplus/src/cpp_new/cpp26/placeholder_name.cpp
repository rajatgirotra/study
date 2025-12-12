/*
 * cpp26 allows you to use the special variable name "_" multiple times in the same function/scope.
 * Everytime you redeclare a variable with the name "_", it hides the previous definition.
 * If there is only one variable with name "_", you can use it as a normal variable. If there are more than one,
 * and you try to use it, it will give you an "ambiguous error". So you really dont need to use std::ignore anymore.
 *
 * also, we try to get into the habit of using std::println() instead of iostream cout.
 */

#include <print>
#include <tuple>

using namespace std;
tuple<int, double, string> getValues() {
    return {10, 50.5, "Hello"};
}

int main() {
    const auto& [age, _, _] = getValues(); // 2 declarations already.

    float _ = 3.5; // 3rd declaration
    int _ = 100;

    // return _; // ambiguous error
    return 0;
}