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


std::function<int(int, int)> returnLambda()
{
    /*auto l = [] (int x, int y) -> int
    {
        return x + y;
    };
    return l; */
     
    return [] (int x, int y) {
        return x*y;
    };
}

int main(int argc, char* argv[])
{
    auto l = returnLambda();
    cout << l(10, 2) << endl;
//    print(l);
}
