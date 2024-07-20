/*
   Here.s a small class that shows the syntax for operator overloading:
 */

//: C12:OperatorOverloadingSyntax.cpp
#include <iostream>
using namespace std;

class Integer {
   int i;
   public:
   Integer(int ii) : i(ii) {}
   const Integer operator+(const Integer& rv) const {
         cout << "operator+" << endl;
         return Integer(i + rv.i);
      }
    Integer& operator+=(const Integer& rv) {
         cout << "operator+=" << endl;
         i += rv.i;
         return *this;
      }

    int display()
    { return i; }
};
int main() {
   cout << "built-in types:" << endl;
   int i = 1, j = 2, k = 3;
   k += i + j;
   cout << "user-defined types:" << endl;
   Integer ii(1), jj(2), kk(3);
   kk += ii + jj;
   cout<<"ii = "<<ii.display()<<endl;
   cout<<"jj = "<<jj.display()<<endl;
   cout<<"kk = "<<kk.display()<<endl;
} ///:~
