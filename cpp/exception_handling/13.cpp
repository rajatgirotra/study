/* Main function throwing an exception; Similarly it can be for any other function too */
#include <iostream>
using namespace std;

int main() try 
{
throw "main";
return 0;
}catch (const char* msg)
{
cout<<"Exception Caught "<<msg<<endl;
}

