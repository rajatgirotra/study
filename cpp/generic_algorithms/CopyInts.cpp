#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int a[] = { 10, 20, 30 };
  const unsigned int size = sizeof(a)/sizeof(a[0]);
  int b[size];
  copy(a, a+size, b);
  for(int i = 0; i < size; ++i)
    cout<<b[i]<<"   ";
  cout<<endl;
  return 0;}
