#include <iostream>
using namespace std;

template<typename T>
class Stack
{
private:
   unsigned long capacity;
   T* data;
   unsigned long index;

public:
   Stack(unsigned long p_capacity);

   ~Stack();

   T& operator[] (unsigned long);
  
   unsigned long getCapacity() const;

};

template<typename T>
Stack<T>::Stack(unsigned long p_capacity = 10) : capacity(p_capacity)
{
   data = new T[capacity];
}

template<typename T>
Stack<T>::~Stack()
{
   if(data)
   {
      delete[] data;
      data = NULL;
   }
}

template<typename T>
T& Stack<T>::operator[] (unsigned long index)
{
   if(index < 0 || index >= capacity)
   {  cout<<"I got hit"<<endl;
      return data[0];
   }
   else
      return data[index];
}

template<typename T>
unsigned long Stack<T>::getCapacity() const
{
   return capacity;
}

int main()
{
   Stack<float>* poStackFloat = new Stack<float>(78);
   int i;
   for ( i = 0; i < 23; ++i)
      poStackFloat->operator[](i) = i * 1.234;

   for ( i = 0; i < 23; ++i)
    cout<<poStackFloat->operator[](i)<<endl;

   cout<<"Capacity = "<<poStackFloat->getCapacity()<<endl;

   delete poStackFloat;

   return 0;
}

   
