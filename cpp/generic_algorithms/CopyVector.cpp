//: C06:CopyVector.cpp
// Copies the contents of a vector.
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>
#include <iostream>
using namespace std;
 
int main() {
  int a[] = { 10, 20, 30 };
  const size_t SIZE = sizeof a / sizeof a[0];
  vector<int> v1(a, a + SIZE);
  vector<int> v2(SIZE);
  copy(v1.begin(), v1.end(), v2.begin());
  assert(equal(v1.begin(), v1.end(), v2.begin()));
} ///:~

/*
 
The first vector, v1, is initialized from the sequence of integers in the array a. The definition of the vector v2 uses a different vector constructor that makes room for SIZE elements, initialized to zero (the default value for integers).

As with the array example earlier, its important that v2 have enough space to receive a copy of the contents of v1. For convenience, a special library function, back_inserter( ), returns a special type of iterator that inserts elements instead of overwriting them, so memory is expanded automatically by the container as needed. The following example uses back_inserter( ), so it doesnt have to establish the size of the output vector, v2, ahead of time:

*/
