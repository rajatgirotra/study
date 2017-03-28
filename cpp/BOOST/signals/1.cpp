// Very simple, signal is just a callback function type.
// slots are actual callback functions.

#include <boost/signals2.hpp>
#include <iostream>


using namespace std;
struct HelloWorld {
    void operator() () {
        cout << "Hello World" << endl;
    }
};
    
int main() {
    boost::signals2::signal<void ()> sig;

    sig.connect(HelloWorld());

    sig();
}
