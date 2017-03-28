/*
Please read 2.cpp first
We'll see here the usage of match_results class.
*/

#include <boost/regex.hpp>
#include <iterator>
#include <iostream>
#include <string>
using namespace std;

int main() {

   //Create a pattern : first 3 digits, followed by 3 words, followed by 1 space, followed by same 3 words as before.
   boost::regex pattern ("(\\d{3})(\\w{2})\\s\\2");
   boost::match_results< std::string::const_iterator > m; 
   string str = "123NA NA";

   bool b = regex_match(str, m, pattern);
   cout << b << endl;

   /* Print the sub-expressions */
   for(boost::match_results< std::string::const_iterator >::const_iterator i = m.begin(); i != m.end(); ++i)
   {
      if(i->matched)
	cout << i->str() << endl;
   }

   return 0;
}
   
