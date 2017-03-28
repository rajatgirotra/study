/* Another example of istream_iterator */

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
list<float> floatList(5);
int i;

cout<<"Enter 5 floating point numbers.. Terminate using Ctrl+Z"<<endl;

istream_iterator<float> cin_iter(cin);
istream_iterator<float> end_of_stream;
copy(cin_iter, end_of_stream, floatList.begin());

cout<<endl;
ostream_iterator<float> ositer(cout, ", ");
copy(floatList.begin(), floatList.end(), ositer);
cout<<endl;
return 0;
}

