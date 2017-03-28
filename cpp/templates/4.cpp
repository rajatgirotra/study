/* Write a function template that can print any standard C++ sequene, be it vector, list or dequeue. */

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
using namespace std;

template <class T, template<class U, class = allocator<U> > class Seq>
void printSeq(Seq<T>& seq)
{
   //typedef typename Seq<T>::iterator iter;
   //for(iter = seq.begin(); iter != seq.end(); ++iter)
   for(typename Seq<T>::iterator iter = seq.begin(); iter != seq.end(); ++iter)
      cout<<*iter<<endl;
}

int main()
{
   vector<int> v;
   v.push_back(1);
   v.push_back(2);
   v.push_back(5);
   v.push_back(3);
   v.push_back(0);

   printSeq(v);

   list<string> l;
   l.push_front("Rajat");
   l.push_front("Vidhu");
   l.push_back("Shweta");
   l.push_back("Jitin");
   printSeq(l);
   return 0;
}

 
