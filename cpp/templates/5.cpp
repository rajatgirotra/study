#include <iostream>
using namespace std;

template <typename T>
class Array
{
   T* data;
   unsigned int size;
   unsigned int capacity;
   static const unsigned int DEFAULT = 10;

public:
   Array(unsigned int cap = DEFAULT) : capacity(cap), size(0)
   {
      data = new T[capacity];
   }

   void push_back(const T& item)
   {
      if(size >= capacity)
      {
         T* newData = new T[2 * capacity];
         for(int i = 0; i < size; ++i)
         {
            newData[i] = data[i];
         }
         delete[] data;
         data = newData;
         capacity = 2 * capacity;
      }
      data[size++] = item;
   }

   T* begin()
   {
      return data;
   }

   T* end()
   {
      return data+size;
   }
};

template <typename T>
const unsigned int Array<T>::DEFAULT;

template<typename T, template<typename> class Seq>
class Container
{
   Seq<T> seq;

public:
   void append(const T& item)
   {
      seq.push_back(item);
   }

   T* begin() { return seq.begin(); }
   T* end () { return seq.end(); }
};

int main()
{
   Container<int, Array> intContainer;
   for(int i = 0; i < 15; ++i)
   {
      intContainer.append(i * 5);
   }

   for(int* p = intContainer.begin(); p != intContainer.end(); ++p)
   {
      cout<<*p<<endl;
   }
}



