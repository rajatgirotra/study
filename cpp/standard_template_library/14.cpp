/* Reverse iterators */
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
  vector<int> objVector;
  int i;
  for(i = 0; i < 10; ++i)
    objVector.push_back(i);

//  for(vector<int>::reverse_iterator iter = objVector.rbegin(); iter != objVector.rend(); ++iter)
 //      cout << *iter ;

  copy(objVector.rbegin(), objVector.rend(), ostream_iterator<int>(cout, "  "));

  return 0;
}

