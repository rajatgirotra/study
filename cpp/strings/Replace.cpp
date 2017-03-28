/* Another form of overloaded replace() function */
#include <iostream>
#include <cassert>
#include <string>
#include <cstddef>
using namespace std;

void replaceChars(string& modifyMe, const string& findMe, const string& replacementString)
{
int i = -10;
i = modifyMe.find(findMe, 0);
if( i != string::npos) /* String returns string::npos if search fails */
modifyMe.replace(i, findMe.size(), replacementString);
cout<<i<<endl;
}

int main()
{
string bigNews = "I think I saw Elvis in a UFO. "
                 "I have been working very hard.";

string replacementString("red T-shirt");
string findMe("UFO");
replaceChars(bigNews, findMe, replacementString);
cout<<bigNews<<endl;
return 0;
}
                
