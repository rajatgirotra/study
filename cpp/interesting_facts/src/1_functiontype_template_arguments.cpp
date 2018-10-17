/* We'll see more about function type template arguments here */

#include <iostream>
using namespace std;

// simple template function which takes a function pointer
template <void (*T)(int& v)>
void doOperation() {
    int temp = 0;
    T(temp);
    cout << "Result is: " << temp << endl;
}


void add1(int& v) {
    v += 1;
}

void add2(int& v) {
    v += 2;
}

#include <iostream>

int main() {
    doOperation<add1>();
    doOperation<add2>();
    return 0;
}

/* Trivial. Here the argument is a Non-Type function pointer.
 * When we pass a function name as a template parameter, it decays to a function pointer. Just like a array decays to
 * its pointer type when passed to a function.
 *
 * Also in C++ an function name is equivalent to its pointer and this is recursive.
 * so MyFunc = &MyFunc== &&&&&&MyFunc (see 2_function_magic.cpp)
 *
 */
