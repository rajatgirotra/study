#include <iostream>
using namespace std;

/* C++11 introduces brace initialization for uniformity.
   int x(0);
   int x = 0;
   int x {0}; are all same

   brace initiazation can also be used for default initialization of non-static data members of a class. 
   class A {
      private:
          int x {0};
          int y = 0; // also ok. C++11/14 code, not C++98
          int z(0); // Error
   };

   On the other hand uncopyable objects cannot be initialized using "=" syntax.
   std::atomic<int> ai {0};
   std::atomic<int> ai = 0; //Error
   std::atomic<int> ai(0); // Ok
   
   So in some cases "=" works and in some "()" works. But "{}" will work everywhere. So its called uniform"

   Advantages: 
   1) brace initialization gives u a warning if you perform a narrowing conversion.
   double x = 3.;
   int y {x};  // Error

   2) It is immune to C++ most vexing parse. Most vexing parse is a rule that states that whatever can be interpreted as a function declration should be treated like one. So for a widget class with a default c'tor, if you write
    Widget w1(); // You are not creating a w1 object, Instead you are declaring a function w1() which return a Widget
    However,
    Widget w1{}; // is fine, it creates w1 as an object of Widget.
*/

struct A {
    int x = 12;
    //int y(0);
    int z{3};
};

int main() {
    double x = 1.;
    int i {x};

    A a;
    cout <<  "A::x " << a.x << endl;
    //cout <<  "A::y " << a.y << endl;
    cout <<  "A::z " << a.z << endl;
    return 0;
}
    
