/*

Read FailedTransform.cpp first

the solution is to write a wrapper function template that calls the correct version of tolower( ) explicitly:

*/

#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

template <typename charT>
charT strToLower(charT c)
{
   return tolower(c);
}

int myToLower(int c)
{
   return tolower(c);
}

int main()
{
   string s("LOWER");
   cout<<"s before = "<<s<<endl;
   //transform(s.begin(), s.end(), s.begin(), &strToLower<int>); // Also note that u are using the address of a template here.
   transform(s.begin(), s.end(), s.begin(), &myToLower);  //-->> This is also fine. You can use any of the two methods you like.
   cout<<"s after = "<<s<<endl;
   return 0;
}
   
