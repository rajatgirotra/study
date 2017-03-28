#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

bool gt15(const int& roInt)
{ return roInt > 15 ;
}

int main()
{
int a[] = { 10, 12, 20, 30, 14 };
const unsigned int size = sizeof(a)/sizeof(a[0]);
int b[size] =  { 0 };

remove_copy_if(a, a+size, b, gt15);
for(int i = 0; i<size; ++i)
cout<<b[i]<<"  ";
return 0;
}

