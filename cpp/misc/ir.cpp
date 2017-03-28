
#include <iostream>
using namespace std;
/* Rev int */
int revInt(int i)
{
    int newNo = 0;
    while(i != 0)
    {
        int tmp = i % 10;
        newNo *= 10;
        newNo += tmp;
        i /= 10;
    }
    return newNo;
}

int main()
{
    cout << revInt(123) << endl;
    return 0;
}
