//: C05:ImplicitCast.cpp

#include <iostream>
using namespace std;
 
template<typename P, typename R>
R implicit_cast(const P& p) {
  return p;
}

int main() {
  int i = 1;
//  float x = implicit_cast<float,int>(i);
 // cout<<x<<endl;
 

//  int j = implicit_cast<int>(x);
  char* p = implicit_cast<char*>(i);
} ///:~

