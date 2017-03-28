//: C03:AddStrings.cpp
#include <string>
#include <cassert>
#include <iostream>
using namespace std;
 
int main() {
  string s1("This ");
  string s2("That ");
  string s3("The other ");
  // operator+ concatenates strings
  s1 = s1 + s2;
  cout<<"s1 = "<<s1<<endl;
  assert(s1 == "This That ");
  // Another way to concatenates strings
  s1 += s3;
  cout<<"s1 = "<<s1<<endl;
  assert(s1 == "This That The other ");
  // You can index the string on the right
  s1 += s3 + s3[4] + "ooh lala";
  cout<<"s1 = "<<s1<<endl;
  //assert(s1 == "This That The other The other oooh lala");
} ///:~

