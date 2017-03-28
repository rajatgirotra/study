#include <boost/signals2.hpp>
#include <iostream>
using std::cout;
using std::endl;

void first() {
    cout << "First " << endl;
}

void second() {
    cout << "Second " << endl;
}

void (*second_ptr)() = &second;

struct third {
    void operator() () {
        cout << "Third " << endl;
    }
};

int main(int argc, char *argv[]) {
    boost::signals2::signal<void()> sig;

    // add at front
    sig.connect([]() {
            cout << "Fourth " << endl;
        }, boost::signals2::at_back);  // connect a lambda.
    sig.connect(first, boost::signals2::at_front);  // connect a simple func.
    sig.connect(1, third());  // connect a function object.
    sig.connect(0, second_ptr);  // connect a function pointer.

    sig();
    return 0;
}
