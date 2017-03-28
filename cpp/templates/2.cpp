#include <iostream>

using namespace std;

static const unsigned int SIZE = 30;

template <class T, unsigned int N = SIZE>
class Stack
{
   T data[N];
   int count;

   public:
   Stack() : count(0)
   { };

   void push(const T& roT)
   {
      if(count < N)
         data[count++] = roT;
      else
      {
         cout<<"Stack Overflow..!!"<<endl;
      }
   }

   T pop()
   {
      if(count > 0)
         return data[--count];

      else
      {
         cout<<"Stack UnderFlow..!!"<<endl;
         return T(0);
      }
   }
};

/* unsigned int N = SIZE is required, so that if you say just "Seq<T> seq" in the class, then it will know that the second argument is SIZE by default
otherwise it will give an error. Also you can say just "unsigned int = SIZE"; the N is redundant. */

template <class T, template<class, unsigned int N = SIZE> class Seq> 
class Container
{
   Seq<T, 20> seq;

   public:
   void push(const T& roT)
   {
      seq.push(roT);
   }

   T pop()
   {
      return seq.pop();
   }
};

int main()
{
   Container<int, Stack> obj;

   int i;

   for(i = 0; i < 22; ++i)
      obj.push(i * 5);

   for(i = 0; i< 22; ++i)
      cout<<obj.pop()<<endl;


   return 0;
}


