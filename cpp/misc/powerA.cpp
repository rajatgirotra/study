#include <iostream>
using namespace std;

unsigned long long powerA(int x, int n)
{
    unsigned long long result = 1;
    for (int i = 1; i <=n; ++i)
    {
        result *= x;
    }
    return result;
}

unsigned long long powerAR(int x, int n)
{
    if(n == 0)
        return 1;
    if(n == 1)
        return x;
    else
        return (x * powerAR(x, n - 1));
}

unsigned long long powerB(unsigned long long x, int n)
{
    if(n == 0)
        return 1;
    if(n == 1)
        return x;
    else if( (n%2) == 0)
        return powerB(x*x, n/2);
    else
        return powerB(x*x, n/2) * x;
}


int main()
{
    cout << powerA(16, 12) << endl;
    cout << powerAR(16, 12) << endl;
    cout << powerB(16, 12) << endl;
    return 0;
}
