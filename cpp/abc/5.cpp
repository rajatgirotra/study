#include <iostream>
using namespace std;

void print(char* str)
{
cout<<str<<endl;
}

int main()
{
const char* str = "sample text";
print(const_cast<char*>(str));
return 0;
}
