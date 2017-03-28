#include <iostream>
using namespace std;

int main()
{

int* const q = new int[10];
q++;
q--;
delete []q;

return 0;
}
