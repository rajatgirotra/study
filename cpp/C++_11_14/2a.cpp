/* To understand the difference between auto and decltype, see below and try to understand */

#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
    auto x = 5; // x is of type int.

    int& ref = x; // ref and x are aliases now.

    auto i = ref; // since ref is a reference type, should i be a reference type too?? No. i will be a simple int type.

    decltype(ref) ii = ref;  // Now ii will be a reference type, so x, ref and ii are all aliases.

    ii++;

    cout << x << ref <<ii << endl; //Will output 666
    cout << i << endl; // will output 5.

    return 0;
}

