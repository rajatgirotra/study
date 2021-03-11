/*
fold expressions allow to apply an operand to all the template arguments.
 before fold expressions were introduced, you needed to write more code to get around the problem.
 Lets see it in action below.
 */

#include <type_traits>
#include <iostream>
#include <functional>
using namespace std;

// a simple variadic template function to get the sum of all the arguments passed to it.
template <typename... T>
auto sum([[maybe_unused]] T&&... t) -> std::common_type_t<T...> {
    [[maybe_unused]] std::common_type_t<T...> result = 0;
    // construct an std::initializer_list of integer. We will just put 0 in the list, but will evaluate the sum of all arguments as a side effect
    std::initializer_list<int> { (result += t, 0)... };
    return result;
}

// now the same sum function again but this time using fold expressions.
template <typename... T>
auto sum2(T&&... t) {
    return (t + ...); // means (t1 + (t2 + (t3 + (t4 + t5)))) assuming 5 function arguments. This is called unary right fold.
    //return (... + t); // means ((((t1 + t2) + t3) + t4) + t5) assuming 5 function arguments. This is called unary left fold.
}

// the unary left and right fold dont look like making a difference with sum/sum2. Let's write a division operation and then
// realize the difference.
template <typename... T>
auto div(T&&... t) {
    return (t / ...);
}

template <typename... T>
auto div2(T&&... t) {
    return (... / t);
}

// write a function to calculate the average of all arguments to a function.
template <typename... T>
auto avg(T&&... t) {
    return (... + t) / sizeof...(T);
}


int main() {
    cout << sum(1, 2, 3.0) << endl;
    cout << sum2(1, 2, 3.0) << endl;

    cout << div(1.0, 2.0, 3.0) << endl; // does ( 1 / ( 2 / 3 ) ) --> 3/2 = 1.5
    cout << div2(1.0, 2.0, 3.0) << endl; // does ( ( 1 / 2) / 3 )  --> 0.5/3 = 0.166667

    cout << avg(1.0, 2.9, 3.0) << endl;

}