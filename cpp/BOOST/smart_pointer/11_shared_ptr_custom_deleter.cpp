/*
You can create a shared_ptr wih a custome deleter. This is a function which gets called when the shared_ptr is about to deallocate the pointer it is holding. The custom deleter takes as argument a pointer to the class that you are managing.
Eg: I am going to write a class which creates a funtion object (operator()), which takes a FILE* argument and closes the file before the FILE object is deleted.
*/

#include <cstdio>
#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;

class FileChoser
{
public:
   void operator() (FILE* poFile)
   {
      cout << "The FileChoser operator() has been called with a FILE*"
	   << " which will now be closed" << endl;

      if(poFile)
      {
         fclose(poFile);
      }
   }
};

int main() try
{
   FILE* poFile = fopen("test.txt", "r");

   if(!poFile) 
   {
      cout << "Unable to open file test.txt" << endl;
      throw "Unable to open file" ;
   }

   boost::shared_ptr<FILE> myFile(poFile, FileChoser());

   fseek(myFile.get(), 42, SEEK_SET);

   myFile.reset();

   cout << "By now, the FILE has been closed." << endl;
} catch(...) {
   cout << "Exception caught" << endl;
}

/*
So when reset is called, and the shared pointer is destroyed, the function object is called.


THE D'TOR OF THE TYPE YOU ARE MANAGING IS NOT AUTOMATICALLY CALLED IN SUCH A CASE.


Actually that second argument can either be a function object or any function address. So instead of creating a FileChoser() class
we could have straight away given the address of fclose() function. The next example does that exactly.
*/

   
