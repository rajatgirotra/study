//: C14:Useful.h
// A class to reuse
#ifndef USEFUL_H
#define USEFUL_H
#include <iostream>
using namespace std;

class X {
  int i;
public:
  X() 
  { 
    cout<<"X::X() called"<<endl;
    i = 5; 
  }
  void set(int ii) { i = ii; }
  int read() const { return i; }
  int permute() { return i = i * 5; }
};
#endif // USEFUL_H ///:~

