#include <boost/signals2.hpp>
#include <iostream>
using namespace std;

struct Hello {
    void operator() () {
        cout << "Hello ";
    }
};

struct World {
    void operator() () {
        cout << ",World " << endl;
    }
};

int main() {
    boost::signals2::signal<void ()> sig;

    sig.connect(Hello());
    sig.connect(World());
    
    sig();
}

// By default, slots are queued at the back.
