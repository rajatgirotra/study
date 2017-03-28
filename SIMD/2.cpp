/*
Print size of various datatypes on this platform
*/
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "size of char   : " << sizeof(char) << endl; //typically 1
    cout << "size of short  : " << sizeof(short) << endl; //2
    cout << "size of integer: " << sizeof(int) << endl; //4
    cout << "size of long   : " << sizeof(long) << endl; //8
    cout << "size of float  : " << sizeof(float) << endl; //4
    cout << "size of double : " << sizeof(double) << endl; //8
    return 0;
}

/*
Assuming the above sizes, a single xmm register can therefore handle/process at the same time either of the following:
16 chars
8 short
4 int
4 floats
2 double
2 long

So if you have two arrays of type int and you want to add them to create a third array, 
then you can use SSE instructions to add 4 integers using a single SSE instruction.

*/
