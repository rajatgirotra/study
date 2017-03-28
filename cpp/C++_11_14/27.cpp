/* Variadic templates: Templates which allow variable number of template arguments.
 * eg:
 * template <typename T, typename ... Types>
 * void print(const T& firstArg, const Types&... args)
 */

#include <iostream>
using namespace std;

void print()
{
}


template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args)
{
    cout << "Number of variable arguments: " << sizeof...(args) << endl;
    cout << firstArg << endl;
    print(args...);
}

int main()
{
    print("ABC", 12, 34.3, 'A', 67L);
    return 0;

}

/*
 * The print gets called recursively and the recursion ends with the no argument print() function defined above
 * Please VERY CAREFULLY NOTE the use of ... at all places, like sizeof... in function parameter, in function call etc.
 */
