#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int main()
{
  vector<char> v;
  v.reserve(41);
 
  strcpy(&v[0], "Hello World");
  strcpy(v.data(), "Hello World");
  
  printf("%s\n", &v[0]);
  printf("%s\n", v.data());

  return 0;
} 

/* 
Refer to "The C++ standard library.pdf" by Nicolai M. Josuttis
*/ 
