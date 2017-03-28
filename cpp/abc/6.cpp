#include <iostream>
using namespace std;

int main()
{
float f = 423.087;
int i = -10;

//i = f;
i = static_cast<int>(f);

cout<<i<<endl;
return 0;
}
