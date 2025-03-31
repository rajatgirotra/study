/*
 * C++17 now guarantees that function evaluation order will now be predicable. Specially, for an expression like
 *
 * foo(std::unique_ptr<T>(new T), otherFunction());
 *
 * the compiler could allocate memory for T, then call otherFunction(), then std::unique_ptr<T> constructor.
 * This could result in memory leak if otherFunction() call throws. That's why the way around it was to use std::make_unique
 *
 * However, C++17 guarantees that
 * 1) the arguments/parameters of a function are still evaluated in any order
 * 2) But, the complete argument and its subexpression must now be evaluated fully before another argument is evaluated
 * so f(a(x), b, c(y));
 * When the compiler chooses to evaluate the first argument - a(x) - then it also needs to evaluate x before processing b or c(y) .
 *
 * An important consequence is this:
 * std::cout << a() << b() << c(); --> this actually transforms to.
 *
 * operator<< (operator<< (operator<<(std::cout, a()), b()), c());
 * before C++17, the order of evaluation of a(), b(), c() was indeterminate.
 * from C++17 onwards, a() is evaluated before b() and b() is evaluated before c()
 *
 */

#include <iostream>
using namespace std;

struct Query {
    Query& addInt(int i) {
        cout << "addInt: " << i << endl;
        return *this;
    }

    Query& addFloat(float f) {
        cout << "addFloat: " << f << endl;
        return *this;
    }
};

float computeFloat() {
    cout << "computing float...\n";
    return 10.5f;
}

int computeInt() {
    cout << "computing int...\n";
    return 9;
}

int main() {
    Query q;
    // compute float has to be called first now, followed by computerInt
    q.addFloat(computeFloat()).addInt(computeInt());
}
