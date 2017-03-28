/*
You can create a shared_ptr wih a custome deleter. This is a function which gets called when the shared_ptr is about to deallocate the pointer it is holding.
*/

#include <cstdio>
#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;

int main() try
{
   FILE* poFile = fopen("test.txt", "r");

   if(!poFile) 
   {
      cout << "Unable to open file test.txt" << endl;
      throw "Unable to open file" ;
   }

   boost::shared_ptr<FILE> myFile(poFile, &fclose);

   fseek(myFile.get(), 42, SEEK_SET);

} catch(...) {
   cout << "Exception caught" << endl;
}
