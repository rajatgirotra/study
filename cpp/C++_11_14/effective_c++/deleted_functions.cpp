/*
We should prefer deleted functions instead of declaring them private and not providing a body.
*/
#include <iostream>
using namespace std;

class A {
private:
    // make copy ctor and assignment operator private
    A(const A&);
    A& operator(const A&);
};

// This is done because you dont want to support it. So if you dont declare the compiler with synthesize for you.
// Also you dont give them a body so that when code like member functions or friend functions try to access these, they will get a link time error.

/* C++11 provides the "= delete;" syntax, which basically means the same but will give you an error at compile time itself instead of link time. So that's an improvement. Also you must define them as public, not private, otherwise when you have client code which tries to use it, they will get compile time error about private access but wont know that infact the function is deleted explicitly */
class B {
public:
    B(const B&) = delete;
    B& operator(const B&) = delete;
};
    
