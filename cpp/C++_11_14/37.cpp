/*
 * Lets now look at std::current_exception(), std::exception_ptr, std::make_exception_ptr(), std::rethrow_exception()
 *
 * You can also store an exception for later processing in a type called std::exception_ptr. This type is just like a shared_ptr. As
 * long as even one pointer is in scope, the exception object will exist.
 *
 * You can create an exception_ptr for the currently handled exception using current_exception().
 * You can create an exception_ptr for any exception class using make_exception_ptr().
 *
 * You can get the exception pointed by the exception_ptr by calling rethrow_exception().
 */

#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
    exception_ptr p;
    #if 1
    try {
        std::logic_error le("logic_error_first");
        throw le;
    } catch(const std::exception& e) {
        p = current_exception();
    }
    #endif


    try {
        rethrow_exception(p); // p must not be null, otherwise you get a seg fault.
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }

    std::logic_error le2("logic_error_second");
    p = make_exception_ptr(le2);

    try {
        rethrow_exception(p); // p must not be null, otherwise you get a seg fault.
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
