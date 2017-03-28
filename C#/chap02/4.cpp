#include <iostream>
using namespace std;

int main()
{
   int j = 20;
   for(int i = 0; i < 10; ++i)
   {
      int j = 80; // Allowed in C++ but not in C#. Read more about C++ data hiding.
      cout<<(j+i)<<endl;
   }
   cout<<j<<endl;
   return 0;
}

