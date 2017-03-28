/*
The explicit keyword is used by the compiler to disable implicit conversion from one type to the other using the one argument c'tor of the class.
Remove the explicit keyword and note the difference in the ouput
*/



#include <iostream>
using namespace std;

class String
{

public: 
   String (int n);//allocate n bytes to the String object 
   String(const char *p); // initializes object with char *p 
   String(const char p); // initializes object with char p 
};

String::String(int n)
{
   cout<<"String::String(int n) called"<<endl;
}

String::String(const char* p)
{
   cout<<"String::String(const char* p) called"<<endl;
}

String::String(const char p)
{
   cout<<"String::String(const char p) called"<<endl;
}


int main()
{
   String myString = 'x';
   String myString2 = 300;
   String myString3 = 125;
   return 0;
}



