#include <iostream>
#include <string>
#include <cstddef>
#include <bitset>
using namespace std;


template <class charT, unsigned int N>
basic_string<charT> bitsetToString(const bitset<N>& bs)
{
   cout << N << endl;
   return bs. template to_string<charT, char_traits<charT>, allocator<charT> > ();
}

/* Bitset class defines to_string as */
/*
template <class charT, class traits, class Allocator>
  basic_string<charT,traits,Allocator> to_string() const;
*/

/* This means that when one should call to_string you should use the exact known type like char or wchar */
/* ie. you could say bs.to_string<char, char_traits<char>, allocator<char> > (); */
/* But since here the exact type will be known only at run time and not at compile time; we have to use the dot template feature */

/* Please refer to DotTemplate2.cpp also */



int main()
{
   bitset<10> bs;
   bs.set();
   //bs.set(5);
   cout<<"bs = "<<bs<<endl;
   string s = bitsetToString<char>(bs);
   cout<<"s = "<<s<<endl;
   return 0;
}


