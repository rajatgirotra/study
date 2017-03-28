/*
 * One problem is shown below.
 */
#include <iostream>
using namespace std;

template <typename Arg>
void print(const Arg& arg)
{
    cout << "I am called" << endl;
    cout << arg << endl;
}

void print()
{
    cout << "I will not get called" << endl;
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
 * Here the following is the call hierarchy
 * print("ABC",      12,34.3,'A',67L);
 * print(12,         34.3,'A',67L);
 * print(34.3,       'A',67L);
 * print('A',        67L);
 * print(67L,        nothing); --> This call is ambiguous because it matches both the variadic template and the one argument template function.
 *
 * However, the compiler resolves it by calling the one argument template function which is considered to be a closer match.
 */
