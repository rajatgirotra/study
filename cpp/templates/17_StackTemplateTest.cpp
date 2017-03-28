#include "14_fibonacci.h"
#include "16_StackTemplate.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
   StackTemplate<int> is;
   for(int i = 0; i < 20; i++)
      is.push(fibonacci(i));
   for(int k = 0; k < 20; k++)
      cout << is.pop() << endl;
   ifstream in("17_StackTemplateTest.cpp");
   assure(in, "17_StackTemplateTest.cpp");
   string line;
   StackTemplate<string> strings;
   while(getline(in, line))
      strings.push(line);
   while(strings.ssize() > 0)
      cout << strings.pop() << endl;
} ///:~
