//: C08:Security.h
#ifndef SECURITY_H
#define SECURITY_H
#include <iostream>
 
class Security {
public:
  virtual ~Security() {}
};
 
class Stock : public Security {};
class Bond : public Security {};
 
class Investment : public Security {
public:
  void special() {
    std::cout << "special Investment function "<<std::endl;
  }
};
 
class Metal : public Investment {};
#endif // SECURITY_H ///:~

