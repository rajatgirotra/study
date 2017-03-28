//: C03:ReplaceAllTest.cpp
//{L} ReplaceAll
#include <cassert>
#include <iostream>
#include <string>
#include "ReplaceAll.h"
using namespace std;
 
int main() {
  string text = "a man, a plan, a canal, Panama";
  cout<<"Text before = "<<text<<endl;
  replaceAll(text, "an", "XXX");
  assert(text == "a mXXX, a plXXX, a cXXXal, PXXXama");
  cout<<"Text after = "<<text<<endl;
} ///:~

