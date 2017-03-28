//Trying to re-declare a local variable in a nested for loop

#include <iostream>
using namespace std;

int main()
{
   int args[5][5];

   for(int i = 0; i < 5; ++i)
   {
      for(int j = 0; j < 5; ++j)
      {
         args[i][j] = (i+j);
      }
   }
}
