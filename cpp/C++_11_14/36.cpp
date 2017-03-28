/* You know already that you can create standard exceptions of logic_error and derived classes and runtime_error and derived class by passing a string argument to the c'tor which is later returned by what().
 *
 * Let's now look at system_error c'tors which also provide you support for creating a code.
 *
 * class system_error : public runtime_error {
 * public:
 *   system_error (error_code ec, const string& what_arg); //use std::make_error_code(std::errc e) to create an error code belonging to generic_category.
 *   system_error (error_code ec, const char* what_arg);
 *   system_error (error_code ec);
 *   system_error (int ev, const error_category& ecat, * const string& what_arg);
 *   system_error (int ev, const error_category& ecat, * const char* what_arg);
 * }
 */

#include <iostream>
#include <system_error>
#include "35.hpp"

using namespace std;

int main()
{
    try {
        system_error se(std::make_error_code(std::errc::destination_address_required), "You know the error");
        throw se;
    } catch (...) {
        processException();
   }

    return 0;
}

    
