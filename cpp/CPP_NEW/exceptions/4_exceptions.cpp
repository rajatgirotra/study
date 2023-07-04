/*
 * Approx. implementation of std::make_exception_ptr
 *
 * template <typename E>
 * std::exception_ptr make_exception_ptr (E e) // note, argument passed by value
 * {
 *     try {
 *         throw e;
 *     } catch(...) {
 *         return std::current_exception();
 *     }
 * }
 *
 * the problem here is that the argument is passed by value.
 */

#include <iostream>
#include <exception>
using namespace std;

std::exception_ptr e, e2;

void handle_exception(std::exception_ptr ex)
{
    try {
        if (ex)
            std::rethrow_exception(ex);
    } catch(const std::exception& exception) {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }
}

int main() {
    try {
        std::string("abcd").substr(42); // will definitely throw
    } catch(std::exception &ex) {
        std::cerr << "(1) Exception: " << ex.what() << std::endl;
        e = std::current_exception();
        e2 = std::make_exception_ptr(ex); // ex is of type std::exception&, so when passed by value to std::make_exception_ptr,
        // template argument E will be std::exception and argument to make_exception_ptr will also be std::exception.
        // so basically object slicing has occurred.
    }
    handle_exception(e);
    handle_exception(e2);
}

