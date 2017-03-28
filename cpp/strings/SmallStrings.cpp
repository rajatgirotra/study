/* Creating and Initializing Strings 

Create an empty string and defer initializing it with character data.

Initialize a string by passing a literal, quoted character array as an argument to the constructor.

Initialize a string using the equal sign (=).

Use one string to initialize another.

*/

//: C03:SmallString.cpp
#include <string>
#include <iostream>
using namespace std;
 
int main() {
  string imBlank;
  string heyMom("Where are my socks?");
  string standardReply = "Beamed into deep " 
              "space on wide angle dispersion?";
  string useThisOneAgain(standardReply);
  cout<<standardReply<<endl;
} ///:~

