#include <iostream>
#include <string>
#include <cstddef>
#include <bitset>
using namespace std;


int main()
{
   bitset<10> bs;
   bs.set(5);
   cout<<"bs = "<<bs<<endl;
   string s = bs.to_string<char, char_traits<char>, allocator<char> > ();
   cout<<"s = "<<s<<endl;
   return 0;
}

