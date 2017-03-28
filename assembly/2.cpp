#include <iostream>
using namespace std;

int main()
{
    int src = 7;
    int dst = 0;

    //copy src to dst and add 1 to dst
    // %0 is output operand, %1 is input operand, $0 means number 0
    asm ("mov %1, %0  \n\t"
            "add $1, %0"
            : "=r"(dst)
            : "r" (src));
    cout << dst << endl;

    return 0;
}
