#include <iostream>
using namespace std;

void foo(const int&)
{
    cout << " foo(const int&)" << endl;
}

#if 1
void foo(int&)
{
    cout << " foo(int&)" << endl;
}
#endif

#if 1
void foo(int&&)
{
    cout << " foo(int&&)" << endl;
}
#endif

int main()
{
    int a = 10;
    const int& p = a;
    foo(a);
    foo(10);
    foo(p);

    return 0;
}
