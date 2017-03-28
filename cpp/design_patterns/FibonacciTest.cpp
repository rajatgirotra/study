#include <iostream>
#include "Fibonacci.h"
using namespace std;

int main()
{
Fibonacci objFibonacci;

for(int i = 0; i < 20; ++i)
cout<<objFibonacci.count()<<" : "<<objFibonacci()<<endl;
//cout<<objFibonacci()<<endl;

return 0;
}

/* 

Observe from the output here that objFibonacci() is called first.. Strange..! is it?? 

*/ 

