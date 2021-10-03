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

/*
 * Note the important thing about std::current_exception().
 * 1) When called outside catch{} (i.e. when there is no active exception being handled), it returns an empty exception_ptr.
 * 2) When called inside catch{}, then the exception_ptr can contain a copy of the active exception or a reference to it (depends on compiler implementation).
 *    However what if another exception is thrown during the copy itself? in that case the exception_ptr object may hold a reference to std::bad_exception.
 */
