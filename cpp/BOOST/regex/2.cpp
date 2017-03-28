/*
Please read 1.cpp first
We'll use regular expression to do validating.
We want that a string should be of the form:  starting with 3 digits, followed by a word, followed by a character, followed by 2 digits or the string N/A, followed by a space, followed by the first word in the patter.
*/

#include <boost/regex.hpp>
#include <string>
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

int main() {
   boost::regex reg("\\d{3}(\\w+).(\\d{2}|N/A)\\s\\1");

   /*
     \d represents a digit - we use \\d because the compiler treats the first \ as an escape sequence
     so we need to escape that.
    
     \w represents a word. you can also use "[a-zA-Z]+" to represent a word.

     \s represents a space.
 
     \1 represents the first subexpression - i.e part of the pattern which is inside parenthesis.
   */

  std::string correct="123Hello N/A Hello";
  std::string incorrect="123Hello 12 hello";
  
  cout << std::boolalpha << boost::regex_match(correct,reg) << endl;
  cout << std::boolalpha << boost::regex_match(incorrect,reg) << endl;

  return 0;
}

/*
Please read 3.cpp next
*/ 
