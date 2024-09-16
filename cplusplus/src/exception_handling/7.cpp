/*

Uncaught exceptions
As we explained in the beginning of this chapter, exception handling is considered better than the traditional return-an-error-code technique because exceptions can.t be ignored, and because the error handling logic is separated from the problem at hand. If none of the exception handlers following a particular try block matches an exception, that exception moves to the next-higher context, that is, the function or try block surrounding the try block that did not catch the exception. (The location of this try block is not always obvious at first glance, since it.s higher up in the call chain.) This process continues until, at some level, a handler matches the exception. At that point, the exception is considered .caught,. and no further searching occurs.

The terminate( ) function
If no handler at any level catches the exception, the special library function terminate( ) (declared in the <exception> header) is automatically called. By default, terminate( ) calls the Standard C library function abort( ) , which abruptly exits the program. On Unix systems, abort( ) also causes a core dump. When abort( ) is called, no calls to normal program termination functions occur, which means that destructors for global and static objects do not execute. The terminate( ) function also executes if a destructor for a local object throws an exception while the stack is unwinding (interrupting the exception that was in progress) or if a global or static object.s constructor or destructor throws an exception. (In general, do not allow a destructor to throw an exception.)

The set_terminate( ) function
You can install your own terminate( ) function using the standard set_terminate( ) function, which returns a pointer to the terminate( ) function you are replacing (which will be the default library version the first time you call it), so you can restore it later if you want. Your custom terminate( ) must take no arguments and have a void return value. In addition, any terminate( ) handler you install must not return or throw an exception, but instead must execute some sort of program-termination logic. If terminate( ) is called, the problem is unrecoverable.

The following example shows the use of set_terminate( ). Here, the return value is saved and restored so that the terminate( ) function can be used to help isolate the section of code where the uncaught exception occurs:

*/

//: C01:Terminator.cpp
// Use of set_terminate(). Also shows uncaught exceptions.

#include <exception>
#include <iostream>
#include <cstddef>
#include <cstdlib>
using namespace std;
 
void terminator() {
  cout << "I'll be back!" << endl;
  exit(0);
}
 
void (*old_terminate)() = set_terminate(terminator);
 
class Botch {
public:
  class Fruit {};
  void f() {
    cout << "Botch::f()" << endl;
    throw Fruit();
  }
  ~Botch() { try {throw 'c';} catch(...){} } 
  //~Botch() { throw 'c'; } // Throwing an exception in a d'tor is bad design or sloppy coding
};
 
int main() {
  try {
    Botch b;
    b.f();
  } catch(Botch::Fruit& e) {
    cout << "inside catch(Botch::Fruit)" << endl;
  }
} ///:~

/*
 
The definition of old_terminate looks a bit confusing at first: it not only creates a pointer to a function, but it initializes that pointer to the return value of set_terminate( ). Even though you might be familiar with seeing a semicolon right after a pointer-to-function declaration, here it.s just another kind of variable and can be initialized when it is defined.

The class Botch not only throws an exception inside f( ), but also in its destructor. This causes a call to terminate( ), as you can see in main( ). Even though the exception handler says catch(...), which would seem to catch everything and leave no cause for terminate( ) to be called, terminate( ) is called anyway. In the process of cleaning up the objects on the stack to handle one exception, the Botch destructor is called, and that generates a second exception, forcing a call to terminate( ). Thus, a destructor that throws an exception or causes one to be thrown is usually a sign of poor design or sloppy coding.

*/
