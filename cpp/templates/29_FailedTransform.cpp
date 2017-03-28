/*

The transform algorithm applies its fourth parameter (tolower( ) in this case) to each character in the string s and places the result in s itself, thus overwriting each character in s with its lower-case equivalent. As it is written, this statement may or may not work! It fails in the following context:

*/


//: C05:FailedTransform.cpp {-xo}
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;
 
int main() {
  string s("LOWER");
  transform(s.begin(), s.end(), s.begin(), tolower);
  cout << s << endl;
} ///:~

/*
 

Even if your compiler lets you get away with this, it is illegal. The reason is that the <iostream> header also makes available a two-argument version of tolower( ) and toupper( ):
template<class charT> charT toupper(charT c,
                                    const locale& loc);
template<class charT> charT tolower(charT c,
                                    const locale& loc);
 

These function templates take a second argument of type locale. The compiler has no way of knowing whether it should use the one-argument version of tolower( ) defined in <cctype> or the one mentioned above. You can solve this problem (almost!) with a cast in the call to transform, as follows:
  transform(s.begin(),s.end(),s.begin()
            static_cast<int (*)(int)>(tolower));
 

(Recall that tolower( ) and toupper( ) work with int instead of char.) The cast above makes clear that the single-argument version of tolower( ) is desired. This works with some compilers, but it is not required to. The reason, albeit obscure, is that a library implementation is allowed to give C linkage (meaning that the function name does not contain all the auxiliary information[56] that normal C++ functions do) to functions inherited from the C language. If this is the case, the cast fails because transform is a C++ function template and expects its fourth argument to have C++ linkage and a cast is not allowed to change the linkage. What a predicament!

*/
