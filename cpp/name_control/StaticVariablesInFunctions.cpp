/*

C and C++ allow you to create a static object inside a function; the storage for this object is not on the stack but instead in the programs static data area. This object is initialized only once, the first time the function is called, and then retains its value between function invocations. For example, the following function returns the next character in the array each time the function is called:

*/


//: C10:StaticVariablesInfunctions.cpp
#include "../require.h"
#include <iostream>
using namespace std;

char oneChar(const char* charArray = 0) 
{
  static const char* s;
  if(charArray) 
  {
    s = charArray;
    return *s;
  }
  else
    require(s, "un-initialized s");

  if(*s == '\0')
    return 0;
  return *s++;
}

char* a = "abcdefghijklmnopqrstuvwxyz";

int main() {
 // oneChar(); // require() fails
  oneChar(a);
  char c;
  while((c = oneChar()) != 0)
  cout << c << endl;
} ///:~

/*

The static char* s holds its value between calls of oneChar( ) because its storage is not part of the stack frame of the function, but is in the static storage area of the program. When you call oneChar( ) with a char* argument, s is assigned to that argument, and the first character of the array is returned. Each subsequent call to oneChar( ) without an argument produces the default value of zero for charArray, which indicates to the function that you are still extracting characters from the previously initialized value of s. The function will continue to produce characters until it reaches the null terminator of the character array, at which point it stops incrementing the pointer so it doesnt overrun the end of the array.


But what happens if you call oneChar( ) with no arguments and without previously initializing the value of s? In the definition for s, you could have provided an initializer,


static char* s = 0;
but if you do not provide an initializer for a static variable of a built-in type, the compiler guarantees that variable will be initialized to zero (converted to the proper type) at program start-up. So in oneChar( ), the first time the function is called, s is zero. In this case, the if(!s) conditional will catch it.


The initialization above for s is very simple, but initialization for static objects (like all other objects) can be arbitrary expressions involving constants and previously declared variables and functions.


You should be aware that the function above is very vulnerable to multithreading problems; whenever you design functions containing static variables you should keep multithreading issues in mind.

*/
