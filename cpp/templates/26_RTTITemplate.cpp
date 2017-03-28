#include <iostream>
#include <typeinfo>
using namespace std;

template <typename T>
class Outer
{
  public:
    template <typename R>
      class Inner
      {
        public:
          void f();
      };
};

template <typename T>
template <typename R>
void Outer<T>::Inner<R>::f()
{
  cout<<"Outer = "<<typeid(T).name()<<endl;
  cout<<"Inner = "<<typeid(R).name()<<endl;
  cout<<"Full  = "<<typeid(*this).name()<<endl;
}

int main()
{

   Outer<float>::Inner<double> obj;
   obj.f();
   cout<<endl;
   Outer<int>::Inner<bool> obj1;
   obj1.f();
   return 0;
}
 


