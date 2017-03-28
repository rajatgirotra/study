#include <iostream>
#include <iterator>
using namespace std;

class MyIterator : public std::iterator<input_iterator_tag, int>
{
private:
   pointer p;
public:

   //C'tor
   MyIterator(int* x) : p(x)
   {}

   //Copy C'tor
   MyIterator(const MyIterator& rhs) : p(rhs.p)
   {}

   //Other operations.
   MyIterator& operator++()
   {
      ++p;
      return *this;
   }
   MyIterator& operator++(int)
   {
      p++;
      return *this;
   }
   int& operator*()
   {
      return *p;
   }
   bool operator == (const MyIterator& myiter)
   {
      return p == myiter.p;
   }
   bool operator != (const MyIterator& myiter)
   {
      return !(this->operator==(myiter));
   }
   
};

int main()
{
   int numbers[] = { 10, 5, 20, 15, 30, 25, 40, 35 };
   MyIterator begin(numbers);
   MyIterator end(numbers + sizeof(numbers)/sizeof(numbers[0]));

   for(MyIterator iter = begin; iter != end; ++iter)
      cout<<*iter<<endl;

   return 0;
}

