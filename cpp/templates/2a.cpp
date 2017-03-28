#include <iostream>
using namespace std;

static const unsigned int SIZE = 30;

template <typename T, unsigned int N = SIZE>
class Stack
{
private:
   T data[N];
   int index;

public:
   Stack();

   void push(const T& item);
   T pop();

   class StackUnderflow
   { };
};

template<typename T, unsigned int N>  //-->Note this
inline Stack<T, N>::Stack() : index(0) 
{
}

template<typename T, unsigned int N> //-- Note this template<typename T, unsigned int N = SIZE> not required
inline void Stack<T,N>::push(const T& item)
{
   if(index < N)
      data[index++] = item;
   else
      cout<<"Stack overflow..!!"<<endl;
}

template<typename T, unsigned int N>
inline T Stack<T,N>::pop()
{
   try
   {
      if(index > 0)
         return data[--index];
      else
         throw StackUnderflow();
   }catch(StackUnderflow&)
   {
      cout<<"No more elements to pop..!!"<<endl;
      return T(0);
   }
}

template <typename T, template<typename T, unsigned int N = SIZE> class Seq>
class Container
{
private:
   Seq<T,20> seq; // note this; cant use Seq<T,N> seq; as N is not a template parameter of this class, it is a template parameter of class Seq.

public:
   void push(const T& item);

   T pop()
   {
      return seq.pop();
   }
};

template <typename T, template<typename T, unsigned int N> class Seq>
inline void Container<T, Seq> :: push(const T& item) // -->> Note this
{
   seq.push(item);
}

int main()
{
   Container<int, Stack> intStack;
   int i = 0;
   
   for(i = 0; i < 10; ++i)
      intStack.push(i * 5);

   for(i = 0; i < 10; ++i)
      cout<<intStack.pop()<<endl;   

   return 0;
}
