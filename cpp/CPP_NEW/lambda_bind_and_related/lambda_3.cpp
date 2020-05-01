/*
 * Because each lambda expression is a unique and anonymous function object,
 * we use the auto keyword to declare an object of type lambda.
 *
 * Now let say you want to specify a lambda as a sorting criteria or as a hash function for a hash table.
 * you can use the decltype() keyword. I'll show u later how this can be done.
 *
 * How would you write a function which returns a lambda?? What will be the return type??
 * It turns out the best way is to use C++ std::function<> class as shown below.
 */

#include <functional>
#include <iostream>
using namespace std;

using my_fn_type = int(int, int);

std::function<my_fn_type> returnLambda() // C++11
// auto returnLambda() // C++14 supports function return value type deduction.
{
    return [] (int x, int y) {
        return x*y;
    };
}

int main()
{
    auto l = returnLambda();
    cout << l(10, 2) << endl;
}
