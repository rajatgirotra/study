#include <iostream>
#include "20_Urand.h"
using namespace std;

int main()
{
Urand<> u; /* The empty <> tell the compiler that templates are involved */
int i = 0;
for(i = 0; i < 10; ++i)
cout<< u() <<endl;
return 0;
}
