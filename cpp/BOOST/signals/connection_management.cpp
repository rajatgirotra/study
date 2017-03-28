// signal.connect() returns an object of type boost::signals2::connection which is used to manage connection b/w the signal and the slot.
#include <boost/signals2.hpp>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;

float add(float a, float b) {
    return a + b;
}

float sub(float a, float b) {
    return a - b;
}

float mul(float a, float b) {
    return a * b;
}

float divi(float a, float b) {
    return a / b;
}

int main(int argc, char *argv[]) {
    boost::signals2::signal<float(float, float)> sig;

    // add all slots
    auto addConn = sig.connect(add);
    auto subConn = sig.connect(sub);
    auto mulConn = sig.connect(mul);
    auto divConn = sig.connect(divi);

    cout << "is divi slot connected: " << std::boolalpha << divConn.connected() << endl;
    cout << "division between 5 and 3:  " << *sig(5.0, 3.0) << endl;  // will return 5/3

    /* You can also temporary disable a slot by creating an instance of boost::signals2::shared_connection_block */
    {
        // By default, creating a shared_connection_block blocks the slot. Pass second argument as
        // false to not block
        boost::signals2::shared_connection_block c(divConn);
        cout << *sig(5.0, 3.0) << endl; // should output 5*3 = 15
        cout << "is divConn blocked: " << std::boolalpha << divConn.blocked() << endl; // should be true
    }
    // connection is unblocked automatically when shared_connection_block goes out of scope.
    cout << "is divConn blocked (after shared_connection_block object goes out of scope): " << std::boolalpha << divConn.blocked() << endl;
    cout << *sig(5.0, 3.0) << endl; // should output 5/3
    divConn.disconnect();
    cout << "is divi slot connected (after disconnect) " << divConn.connected() << endl;
    cout << *sig(5.0, 3.0) << endl;  // will return 5*3 as divi has been disconnected()
    cout << "is divConn blocked (after connection is explicitly disconnected): " << std::boolalpha << divConn.blocked() << endl;

    return 0;
}


