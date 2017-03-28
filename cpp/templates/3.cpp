/* Write a program using templates to pass STL vectors and lists as template arguments */
/* vector is declared in the C++ library as:
   template <class T, class Allocator = allocator<T> > vector;
*/

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <class T, template<class U, class Allocator = allocator<U> > class Seq> // --> You can remove the Allocator word if you want. It still compiles.
class Container
{
   Seq<T> seq;

public:
   void push_back(const T& roT)
   {
      seq.push_back(roT);
   }

   typename Seq<T>::iterator begin()
   {
      return seq.begin();
   }

   typename Seq<T>::iterator end()
   {
      return seq.end();
   }
};

int main()
{
//Use Container as a list 
   Container<int, list> objList;
   objList.push_back(1);
   objList.push_back(387);
   objList.push_back(-6798);

   for(list<int>::iterator p = objList.begin(); p != objList.end(); ++p)
      cout<<*p<<endl;
   cout<<endl<<endl;


//Use Container as a vector
   Container<string, vector> objVector;
   objVector.push_back("Rajat");
   objVector.push_back("Vidhu");
   objVector.push_back("Jitin");
   objVector.push_back("Shweta");

   for(vector<string>::iterator x = objVector.begin(); x != objVector.end(); ++x)
      cout<<*x<<endl;
 
   return 0;
}
   

