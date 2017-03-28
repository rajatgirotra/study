#include <iostream>
using namespace std;

typedef int function_type(int);

int callFunction(const function_type& foo, int param)
{
    return foo(param);
}

function_type a, b;

int main()
{
    cout << callFunction(a, 10) << endl;
    cout << callFunction(b, 10) << endl;

    return 0;
}

int a(int param)
{
    return (param * 5);
}

int b(int param)
{
    return (param + 6);
}

