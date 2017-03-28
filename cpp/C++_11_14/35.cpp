#include "35.hpp"

#include <stdexcept>
#include <system_error>
#include <future>
#include <iostream>

template <typename T>
void processCodeException(const T& e)
{
    using namespace std;
    auto c = e.code();
    cerr << "- category: " << c.category().name() << endl;
    cerr << "- value: "    << c.value() << endl;
    cerr << "- message: "  << c.message() << endl;
    cerr << "- def error condition:" << endl;
    cerr << "\t-def category: " << c.default_error_condition().category().name() << endl;
    cerr << "\t-def value: " << c.default_error_condition().value() << endl;
    cerr << "\t-def message: " << c.default_error_condition().message() << endl;
}

void processException() noexcept
{
    using namespace std;
    try {
        throw; //rethrow exception to handle it here
    } /*catch(const ios_base::failure& e) {
        cerr << "I/O EXCEPTION: " << e.what() << endl;
        processCodeException(e);
   
        g++4.8.2 or 4.9.2 does not have std::io_errc implemented yet
    } */ catch(const system_error& e) {
        cerr << "SYSTEM EXCEPTION: " << e.what() << endl;
        processCodeException(e);
    } catch(const future_error& e) {
        cerr << "FUTURE EXCEPTION: " << e.what() << endl;
        processCodeException(e);
    } catch(const bad_alloc& e) {
        cerr << "BAD ALLOC EXCEPTION: " << e.what() << endl;
    } catch(const exception& e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    } catch(...) {
        cerr << "EXCEPTION (unnknown): " << endl;
    }
}
