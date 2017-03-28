/*

Pure virtual destructors
While pure virtual destructors are legal in Standard C++, there is an added constraint when using them: you must provide a function body for the pure virtual destructor. This seems counterintuitive; how can a virtual function be pure if it needs a function body? But if you keep in mind that constructors and destructors are special operations it makes more sense, especially if you remember that all destructors in a class hierarchy are always called. If you could leave off the definition for a pure virtual destructor, what function body would be called during destruction? Thus, its absolutely necessary that the compiler and linker enforce the existence of a function body for a pure virtual destructor.


If its pure, but it has to have a function body, whats the value of it? The only difference youll see between the pure and non-pure virtual destructor is that the pure virtual destructor does cause the base class to be abstract, so you cannot create an object of the base class (although this would also be true if any other member function of the base class were pure virtual).


Things are a bit confusing, however, when you inherit a class from one that contains a pure virtual destructor. Unlike every other pure virtual function, you are not required to provide a definition of a pure virtual destructor in the derived class. The fact that the following compiles and links is the proof:

*/
#include <iostream>
using namespace std;
//: C15:UnAbstract.cpp
// Pure virtual destructors 
// seem to behave strangely

class AbstractBase {
public:
  virtual ~AbstractBase() = 0;
};

AbstractBase::~AbstractBase() { cout<<"ABC"<<endl;}

class Derived : public AbstractBase {};
// No overriding of destructor necessary?

int main() { Derived d; } ///:~

