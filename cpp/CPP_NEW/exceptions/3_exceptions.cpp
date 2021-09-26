#include <iostream>
#include <thread>
#include <exception>
#include <string>
using namespace std;

int main() {
    std::exception_ptr eptr;

    // raise and catch exception, then capture it using std::current_exception()
    try {
        std::string().at(1); // will raise exception
    } catch(...) {
        eptr = std::current_exception();
    }

    // handle exception on a separate thread.
    auto t = std::thread([eptr]() {
        try {
            std::rethrow_exception(eptr);
        } catch(const std::exception& e) {
            cout << "caught exception: " << e.what() << endl;
        }
    });

    t.join();
}
