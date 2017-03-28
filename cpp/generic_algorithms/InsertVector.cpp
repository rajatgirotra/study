#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <cassert>
#include <vector>
using namespace std;

int main()
{
int a[] = { 10, 20, 30 };
const unsigned int size = sizeof(a)/sizeof(a[0]);
vector<int> v1 (a, a+size);
vector<int> v2; // v2 is empty here
cout<<"Size of vector v2 = "<<v2.size()<<endl;

copy(v1.begin(), v1.end(), back_inserter(v2));
cout<<"Size of vector v2 after doing the copy = "<<v2.size()<<endl;
assert(equal(v1.begin(), v1.end(), v2.begin()));
return 0;
}

/*
I'll know show how cleverly is the back_inserter() function written.
You know already that a copy() function is like this:

template <InputIterator input, OutputIterator output>
void copy(InputIterator first, InputIterator last, OutputIterator result)
{
   while(first != last)
      *result++ = *first++;
}

Now back_inserter() is actually a template function which returns an iterator object of type "back_insert_iterator"

i.e. you have:

template <class Container>
back_insert_iterator<Container> back_inserter(Container& x); //not const Container& xl as we'll be copying elements into it.

for example, in the above example, it will return an iterator object of type back_insert_iterator<vector<int> >;

Now back_insert_iterator is a special iterator object which overloads the assignment operator to call the push_back() function on the template parameter object it holds.
i.e

template <class Container>
class back_insert_iterator : public iterator<output_iterator_tag, void, void, void, void, void>
{
protected:
   Container* container; //taking the above example, this will be vector<int>* container; 

public:
   typedef Container container_type;

   explicit back_insert_iterator(Container& x) : container(&x)
   { }

   back_insert_iterator<Container>& operator = (typename Container::const_reference value)
   {   container->push_back(value); }

   back_insert_iterator<Container>& operator ++()
   { return *this; }

   back_insert_iterator<Container>& operator ++(int)
   { return operator++(); }
 
   back_insert_iterator<Container>& operator *() 
   {   return *this; }
};

See how cleverly have the operators being overloaded & relate to the use of the iterator inside the copy function.
*/

