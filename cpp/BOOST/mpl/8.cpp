/*
 * Before you read 9.cpp to see various type traits, there is something you need to know first
 * You know what are integral types. There is something called as a function type.
 *
 * typedef int f1();
 * defines f1 to be a function type which returns an int and takes a void.
 *
 * f1 foo; declares a prototype for such a function. ie. its equivalent to.
 *
 * int foo();
 *
 */

#include <iostream>
#include <string>
using namespace std;

typedef int f1(const string&);

f1 foo; //prototype for a function foo which takes a string and returns an int. Function foo not defined yet.

int main()
{
    cout << foo("Hello World") << endl;

    f1* pFunc = &foo;  //Declaring a pointer to a function.
    f1& pRef = foo;  //declaring a reference to a function.
    cout << (*pFunc)("Hello World") << endl;
    cout << pRef("Hello World") << endl;
    return 0;
}

#if 0
int foo(const string&)
{
    return 100;
}
#endif

/* This function will not compile as we are missing the definition of function foo.
 */
