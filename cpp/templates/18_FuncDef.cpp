/*

Default template arguments
You can provide default arguments for template parameters in class templates, but not function templates. As with default function arguments, they should only be defined once, the first time a template declaration or definition is seen by the compiler. Once you introduce a default argument, all the subsequent template parameters must also have defaults. To make the fixed-size Stack template shown earlier a little friendlier, for example, you can add a default argument like this:

template<class T, size_t N = 100> class Stack {
  T data[N];  // Fixed capacity is N
  size_t count;
public:
  void push(const T& t);
  // Etc.
};
 
Now, if you omit the second template argument when declaring a Stack object, the value for N will default to 100.

You can choose to provide defaults for all arguments, but you must use an empty set of brackets when declaring an instance so that the compiler knows that a class template is involved:

template<class T = int, size_t N = 100>  // Both defaulted
class Stack {
  T data[N];  // Fixed capacity is N
  size_t count;
public:
  void push(const T& t);
  // Etc.
};
 
Stack<> myStack;  // Same as Stack<int, 100>
 
Default arguments are used heavily in the Standard C++ library. The vector class template, for instance, is declared as follows:

template<class T, class Allocator = allocator<T> >
class vector;
 
Note the space between the last two right angle bracket characters. This prevents the compiler from interpreting those two characters (>>) as the right-shift operator.

This declaration reveals that vector takes two arguments: the type of the contained objects it holds, and a type that represents the allocator used by the vector. Whenever you omit the second argument, the standard allocator template is used, parameterized by the first template parameter. This declaration also shows that you can use template parameters in subsequent template parameters, as T is used here.

Although you cannot use default template arguments in function templates, you can use template parameters as default arguments to normal functions. The following function template adds the elements in a sequence:

*/

//: C05:FuncDef.cpp
#include <iostream>
using namespace std;
 
template<class T> T sum(T* b, T* e, T init = T{}) {
  while(b != e)
    init += *b++;
  return init;
}
 
int main() {
  int a[] = { 1, 2, 3 };
  cout << sum(a, a + sizeof a / sizeof a[0]) << endl; // 6
  string s[] = { "I", " am", " Rajat" };
  cout<<sum(s, s + sizeof(s)/sizeof(s[0]))<<endl;
} ///:~

/*
 
The third argument to sum( ) is the initial value for the accumulation of the elements. Since we omitted it, this argument defaults to T( ), which in the case of int and other built-in types invokes a pseudo-constructor that performs zero-initialization.

The third parameter is T init = T(); i.e int init = int(); which creates and integer variable init with default value as 0.

*/
