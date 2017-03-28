/* Write a program that returns the summation and the difference of two integers. Use the same function and demonstrate the usage of "pair" class in C++ */

#include <iostream>
#include <utility>
using namespace std;

typedef pair<int, int> Pair;


Pair compute(int a, int b)
{
   int sum = a + b;
   int diff = a - b;
   return make_pair(sum, diff);
}

int main()
{
   int a;
   int b;
   cout<<"Enter a = ";
   cin>>a;
   cout<<"Enter b = ";
   cin>>b;

   Pair p = compute(a, b);
   cout<<"Sum  = "<<p.first<<endl;
   cout<<"Diff = "<<p.second<<endl;
   
   return 0;
} 
   
