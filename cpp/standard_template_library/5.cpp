//: C06:CopyIntsFromFile.cpp
// Uses an input stream iterator.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
//#include "../require.h"
using namespace std;
 
bool gt15(int x) { return 15 < x; }
 
int main() {
  ofstream ints("someInts.dat");
  ints << "1 3 47 5 84 9";
  ints.close();
  ifstream inf("someInts.dat");
 // assure(inf, "someInts.dat");
  remove_copy_if(istream_iterator<int>(inf),
                 istream_iterator<int>(),
                 ostream_iterator<int>(cout, "\n"), gt15);
} ///:~

/* 
The first argument to replace_copy_if( ) in this program attaches an istream_iterator object to the input file stream containing ints. The second argument uses the default constructor of the istream_iterator class. This call constructs a special value of istream_iterator that indicates end-of-file, so that when the first iterator finally encounters the end of the physical file, it compares equal to the value istream_iterator<int>( ), allowing the algorithm to terminate correctly. Note that this example avoids using an explicit array altogether.
*/
