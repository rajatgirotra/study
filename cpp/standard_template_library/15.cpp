#include <iostream>
#include <vector>
#include <list>
#include "15.h"
using namespace std;

int main()
{
   vector<int> objVector;
   int i;
   for(i = 0; i < 10; ++i)
      objVector.push_back(i*5);

   PRINT_ELEMENTS(objVector, "all vector elements: ");

   list<string> strList;
   strList.push_back("ABC"); 
   strList.push_back("abc"); 
   PRINT_ELEMENTS(strList, "all list elements: ");

   return 0;
}

