/* The standard says that lambdas are implicitly convertible to function pointers if and only if lambdas are stateless (ir they do not capture scope). */

#include <iostream>
using namespace std;

using Func_t = void (*)(double, bool);


int main() {
    auto l1 = [](double, bool) {};
    Func_t foo1 = l1;
    auto l2 = [=](double, bool) {}; // l2 captures scope.
    Func_t foo2 = l2; // error. 
}

/* Why this restriction. Think how the variables in scope are captured?? 
1) The compiler can pass the variables as arguments to lambda. But where do we pass the arguments. in the beginning, last or middle. plus this doesnt look right because when you will call, you will only pass the 2 two args double and bool you specified.

2) The other way is to create a class inside the lambda and create variables there. Then that class can define a function object which actually accepts the double and bool and becomes the actual function object. So cannot be converted to a function pointer, as most likely it is a member function.
*/

