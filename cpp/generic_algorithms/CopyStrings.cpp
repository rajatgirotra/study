#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;

int main()
{
  string a[] = { "red", "green", "blue" };
  cout << sizeof(a) << endl;
  const unsigned int size = sizeof(a)/sizeof(a[0]);

  cout<<"Size of string array a = "<<size<<endl;
  string b[size];
  copy(a, a+size, b);
  for(int i = 0; i < size; ++i)
  {
    cout<<b[i]<<"   ";
  }
  assert(equal(a, a+size, b));
  cout<<endl;
  return 0;
}

/*
The copy( ) algorithms first two parameters represent the range of the input sequencein this case the array a. Ranges are denoted by a pair of pointers. The first points to the first element of the sequence, and the second points one position past the end of the array (right after the last element). This may seem strange at first, but it is an old C idiom that comes in quite handy. For example, the difference of these two pointers yields the number of elements in the sequence.
*/
