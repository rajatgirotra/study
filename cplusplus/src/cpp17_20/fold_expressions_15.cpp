/*
fold expressions allow to apply an operand to all the template arguments.
 before fold expressions were introduced, you needed to write more code to get around the problem.
 Let's see it in action below.
 */

#include <type_traits>
#include <iostream>
#include <functional>
using namespace std;

// a very primitive way to calculate sum of all template arguments
auto sum_primitive() { return 0; }

template <typename T, typename... Rest>
auto sum_primitive(T&& arg, Rest&&... rest) {
    return arg + sum_primitive(rest...);
}

// a simple variadic template function to get the sum of all the arguments passed to it.
template <typename... T>
auto sum([[maybe_unused]] T&&... t) {
    [[maybe_unused]] std::common_type_t<T...> result = 0;
    // construct a std::initializer_list of integer. We will just put 0 in the list, but will evaluate the sum of all arguments as a side effect
    (void)std::initializer_list<int> { (result += t, 0)... };
    return result;
}

// now the same sum function again but this time using fold expressions.
template <typename... T>
auto sum2(T&&... t) {
    return (t + ...); // means (t1 + (t2 + (t3 + (t4 + t5)))) assuming 5 function arguments. This is called unary right fold.
    //return (... + t); // means ((((t1 + t2) + t3) + t4) + t5) assuming 5 function arguments. This is called unary left fold.
}

// the unary left and right fold don't look like making a difference with sum/sum2. Let's write a division operation and then
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
    cout << sum_primitive(1, 2, 3.5) << endl;
    cout << sum(1, 2, 3.0) << endl;
    cout << sum2(1, 2, 3.0) << endl;

    cout << div(1.0, 2.0, 3.0) << endl; // does ( 1 / ( 2 / 3 ) ) --> 3/2 = 1.5
    cout << div2(1.0, 2.0, 3.0) << endl; // does ( ( 1 / 2) / 3 )  --> 0.5/3 = 0.166667

    cout << avg(1.0, 2.9, 3.0) << endl;
}

/*
 * (init op ... op e) --> this is also left fold as 'e' is the variadic template argument. But this is called binary left fold as you can
 * specify an expression as an init expression. this is equivalent to ((((init op e1) op e2) op e3) op e4)
 *
 * similarly.
 * (e op ... op init) --> is binary right fold. this is equivalent to (e1 op (e2 op (e3 op (e4 op init))))
 *
 * op can be any of the 32 binary operators. i.e  * + - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*.
 *
 * Try to write a template function called FoldPrint() that takes variadic template argument and prints all of its args using binary left fold
 */
