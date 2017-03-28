/* Stream iterators allow you to treat files and I/O devices (such as cin and cout) as if they were iterators */
/* This makes it easy to use files and I/O devices as arguments to algorithms */

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
int arr[] = { 10, 20, 30, 40, 50 };
list<int> intList;
int i;

for(i = 0; i < 5; ++i)
intList.push_back(arr[i]);

ostream_iterator<int> ositer(cout, ", ");

cout<<"Contents of the file.."<<endl;

copy(intList.begin(), intList.end(), ositer);
cout<<endl;
return 0;
}

