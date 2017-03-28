#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int gt15(const int& roInt)
{
   return roInt > 15;
}

int main()
{
int a[] = { 10, 20, 30, 14 };
const unsigned int size = sizeof(a)/sizeof(a[0]);

remove_copy_if(a, a+size, ostream_iterator<int>(cout, ",  "), gt15);

return 0;
}
