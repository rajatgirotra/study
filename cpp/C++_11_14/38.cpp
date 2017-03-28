/*
 * C++11 also provides a class nested::exception, this can hold another exception.
 * Just like you have the cause object in Java. So you have an outer exception and a nested exception.
 */

#include <iostream>
#include <stdexcept>

using namespace std;

void printException(const std::exception& e)
{
    cerr << e.what () << endl;
    try {
        std::rethrow_if_nested(e);
    } catch(const std::exception& e1) {
        cerr << "\t nested: " << e1.what() << endl;
    }
}
  

void ThrowException() {
    try {
        std::logic_error le("logic_error_first");
        throw le;
    } catch (const std::exception& e) {
        nested_exception ne; // the default c'tor creates the nested exception with an exception_ptr initialised with current_exception()
                             // or a null exception_ptr if there is no current exception.
        //throw_with_nested(ne);
        throw_with_nested(std::logic_error("logic_error_second")); // this is the outer exception. Inner exception is logic_error_first.
    }
}
int main()
{
    try {
        ThrowException(); 
    }catch(const std::exception& e) {
        printException(e);
    }catch(...) {
        cerr << "Exception (unknown)" << endl;
    }
   
    return 0;
}
