/* Probably you never saw this before, but C++11 has introduced reference qualifiers (& or &&) to be added after the member function declaration of a class.

void doWork() &; // means that this function can only be called when *this is an lvalue
void doWork() &&; // means that this function can only be called when *this is an rvalue.

Also the reference qualifier is part of the function signature.
*/

#include <iostream>
#include <memory>
using namespace std;

class Base {
public:
    virtual void doWork() & {
        cout << "Base::doWork() &" << '\n';
    }
};

class Derived : public Base {
public:
    //void doWork() override { //!! Error-doesn't actually override unless you put "&" reference qualifier.
    void doWork() & override {
        cout << "Derived::doWork()" << '\n';
    }
};

int main() {
    // Base().doWork(); //!! Error. "doWork() &" should be called with lvalue *this
    std::unique_ptr<Base> upb = std::make_unique<Derived>(); // also see how make_unique is called. Just specify the template type with empty arguments. It will automatically construct an object of type Derived.
    upb->doWork();
    return 0;
}
