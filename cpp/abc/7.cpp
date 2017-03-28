#include <iostream>
using namespace std;

int main()
{
int i = 10;
int* poInt = 0;

poInt = static_cast<int*>(i);
//poInt = reinterpret_cast<int*>(i);

cout<<poInt<<endl;
return 0;
}
