/*
Lets assume you have a class Widget with c'tor
   Widget (int, double) --> A
   Widget (int, bool) --> B

   Widget w1(10, 5.); --> Matches A
   Widget w2{10, 5.}; --> brace initialization, Matches A
   Widget w3(10, true) --> Matches B
   Widget w4{10, true}; --> brace initialization, Matches B

All good so far. However, let say we add a c'tor which takes an std::initializer_list

   Widget(std::initializer_list<long double> lst) --> C
   Now both,
   Widget w2{10, 5.}; 
   Widget w4{10, true};
matches c'tor C, even though the type of initializer_list (long double) is a worse match than c'tor A and B which are exact matches.

  The rule is that if there is any way the compiler can construe a call having brace initialization to be to the c'tor which takes initializer_list, the compiler will do so. 

  Eg: Lets say Widget has
   
   operator float();

   and you create Widget object like
   Widget w1{w2}; // looks like copy c'tor  but no, the compiler can convert w2 to float and then call the std::initializer_list c'tor for long double.

   Even if you have std::initializer_list<bool>, the compiler will report an error:
    Widget w1{10, 5.}; // error 5.0 is a  narrowing cast from double to bool. Lets try this actually.

Only if there’s no way to convert the types of the arguments in a braced initializer to the type in a std::initializer_list do compilers fall back on normal overload resolution.

The last rule is that when you have a default c'tor and a c'tor with initializer_list, and you create an object with empty braces, you get default construction. Empty braces mean no arguments, not initializer_list with no elements.
*/

#include <iostream>
#include <initializer_list>
#include <string>
using namespace std;

class Widget {
public:
    Widget(int a, double d) {
        cout << "Widget (int a, double d)" << endl;
    }

    // Widget(std::initializer_list<bool> bi) {
    //     cout << "std::initializer_list<bool>" << endl;
    // }

    Widget(std::initializer_list<string> si) {
        cout << "std::initializer_list<string>" << endl;
    }
};

int main() {
    Widget w1(10, 4.);
    /* 
      really this is an error with the c'tor initializer_list<bool> enabled.
      with c'tor initializer_list<string> the compiler cannot convert 10 and 4. to string implicitly, so normal c'tor will be called.
    */
    Widget w2{10, 4.};  
     
    return 0;
}
  
