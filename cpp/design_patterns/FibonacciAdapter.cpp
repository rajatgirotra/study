/*

Perhaps you would like to take this generator and perform STL numeric algorithm operations with it. Unfortunately, the STL algorithms only work with iterators, so you have an interface mismatch. The solution is to create an adapter that will take the FibonacciGenerator and produce an iterator for the STL algorithms to use. Since the numeric algorithms only require an input iterator, the Adapter is fairly straightforward (for something that produces an STL iterator, that is):

*/

//: C10:FibonacciAdapter.cpp
// Adapting an interface to something you already have.
#include <iostream>
#include <numeric>
#include "Fibonacci.h"
#include "PrintSequence.h"
using namespace std;
 
class FibonacciAdapter { // Produce an iterator

  Fibonacci f;
  int length;

public:

  FibonacciAdapter(int size) : length(size) {}
  class iterator;
  friend class iterator;
  class iterator : public std::iterator<
    std::input_iterator_tag, FibonacciAdapter, ptrdiff_t> {
    FibonacciAdapter& ap;
  public:
    typedef int value_type;
    iterator(FibonacciAdapter& a) : ap(a) {}
    bool operator==(const iterator&) const {
      return ap.f.count() == ap.length;
    }
    bool operator!=(const iterator& x) const {
      return !(*this == x);
    }
    int operator*() const { return ap.f(); }
    iterator& operator++() { return *this; }
    iterator operator++(int) { return *this; }
  };
  iterator begin() { return iterator(*this); }
  iterator end() { return iterator(*this); }
};
 
int main() {
  const int SZ = 20;
  FibonacciAdapter a1(SZ);
  cout << "accumulate: "
    << accumulate(a1.begin(), a1.end(), 0) << endl;
  FibonacciAdapter a2(SZ), a3(SZ);
  cout << "inner product: "
    << inner_product(a2.begin(), a2.end(), a3.begin(), 0)
    << endl;
  FibonacciAdapter a4(SZ);
  int r1[SZ] = {0};
  int* end = partial_sum(a4.begin(), a4.end(), r1);
  print(r1, end, "partial_sum", " ");
  FibonacciAdapter a5(SZ);
  int r2[SZ] = {0};
  end = adjacent_difference(a5.begin(), a5.end(), r2);
  print(r2, end, "adjacent_difference", " ");
} ///:~

/*
 
You initialize a FibonacciAdapter by telling it how long the Fibonacci sequence can be. When an iterator is created, it simply captures a reference to the containing FibonacciAdapter so that it can access the FibonacciGenerator and length. Note that the equivalence comparison ignores the right-hand value because the only important issue is whether the generator has reached its length. In addition, the operator++( ) doesnt modify the iterator; the only operation that changes the state of the FibonacciAdapter is calling the generator function operator( ) on the FibonacciGenerator. We can get away with this extremely simple version of the iterator because the constraints on an Input Iterator are so strong; in particular, you can only read each value in the sequence once.

In main( ), you can see that all four different types of numeric algorithms are successfully tested with the FibonacciAdapter.

*/
