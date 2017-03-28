#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
using namespace std;

ofstream out("int.dat");

int main()
{
   list<string> strList;
   strList.push_back("Rajat");
   strList.push_back("Vidhu");
   strList.push_back("Ankit");
   strList.push_back("Richa");
   strList.push_back("Isha");
   strList.push_back("Puneet");

   out << "1 2 3 4 5 6 7 8" ;
   out.close();

   ifstream in("int.dat");

   copy(strList.begin(), strList.end(), ostream_iterator<string>(cout, ": "));
   cout<<endl;
   copy(istream_iterator<int>(in), istream_iterator<int>(), ostream_iterator<int>(cerr, ": "));
   
}


