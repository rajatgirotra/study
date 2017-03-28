/*

Explicit specialization

You can also provide the code yourself for a given template specialization, should the need arise. Providing your own template specializations is often needed with class templates, but we will begin with the min( ) function template to introduce the syntax.

Recall that in MinTest.cpp earlier in this chapter we introduced the following ordinary function:
const char* min(const char* a, const char* b) {
  return (strcmp(a, b) < 0) ? a : b;
}
 

This was so that a call to min( ) would compare strings and not addresses. Although it would provide no advantage here, we could instead define a const char* specialization for min( ), as in the following program:

*/

//: C05:MinTest2.cpp
#include <cstring>
#include <iostream>
using std::strcmp;
using std::cout;
using std::endl;
 
template<class T>
const T& min(const T& a, const T& b)
{
  return (a < b) ? a : b;
}
 
// An explicit specialization of the min template
template<>
const char* const& min<const char*>(const char* const& a,
                                    const char* const& b) {
  return (strcmp(a, b) < 0) ? a : b;
}
 
int main() {
  const char *s2 = "say \"Ni-!\"", *s1 = "knights who";
  cout << min(s1, s2) << endl;
  cout << min<>(s1, s2) << endl;
} ///:~

/* 

The template<> prefix tells the compiler that what follows is a specialization of a template. The type for the specialization must appear in angle brackets immediately following the function name, as it normally would in an explicitly specified call. Note that we carefully substitute const char* for T in the explicit specialization. Whenever the original template specifies const T, that const modifies the whole type T. It is the pointer to a const char* that is const. So we must write const char* const in place of const T in the specialization. When the compiler sees a call to min( ) with const char* arguments in the program, it will instantiate our const char* version of min( ) so it can be called. The two calls to min( ) in this program call the same specialization of min( ).

Explicit specializations tend to be more useful for class templates than for function templates. When you provide a full specialization for a class template, though, you may need to implement all the member functions. This is because you are providing a separate class, and client code may expect the complete interface to be implemented.

The standard library has an explicit specialization for vector when it holds objects of type bool. The purpose for vector<bool> is to allow library implementations to save space by packing bits into integers.[60]

As you saw earlier in this chapter, the declaration for the primary vector class template is:
template<class T, class Allocator = allocator<T> >
class vector {...};
 

To specialize for objects of type bool, you could declare an explicit specialization as follows:
template<> class vector<bool, allocator<bool> > {...};
 

Again, this is quickly recognized as a full, explicit specialization because of the template<> prefix and because all the primary templates parameters are satisfied by the argument list appended to the class name.

*/
