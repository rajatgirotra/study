/* Reverse iterator */
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
int arr[] = { 23, -98, 788, 127, 5423, -3489, 4, 3532, -975, 0 };

vector<int> intVector(arr, arr + sizeof(arr)/sizeof(arr[0]));

auto revIter = intVector.crbegin();

while( revIter != intVector.crend() )
    cout<<*revIter++<<endl;

return 0;
}

