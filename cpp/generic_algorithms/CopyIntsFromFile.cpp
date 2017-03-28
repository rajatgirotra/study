#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
using namespace std;
ofstream outf("SomeInts.dat");
ifstream inf("SomeInts.dat");

bool gt15(const int& roInt)
{
 return roInt > 15 ;
}

int main()
{
outf<<"1 34 12 15 20 30 -65";
outf.close();

replace_copy_if(istream_iterator<int>(inf), istream_iterator<int>(), ostream_iterator<int>(cout, "  "), gt15, -99);
return 0;
}

/*
The first argument to replace_copy_if( ) in this program attaches an istream_iterator object to the input file stream containing ints. The second argument uses the default constructor of the istream_iterator class. This call constructs a special value of istream_iterator that indicates end-of-file, so that when the first iterator finally encounters the end of the physical file, it compares equal to the value istream_iterator<int>( ), allowing the algorithm to terminate correctly. Note that this example avoids using an explicit array altogether.

*/
