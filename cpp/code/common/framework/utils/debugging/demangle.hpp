#ifndef _COMMON_FRAMEWORK_UTILS_DEMANGLE_HPP_
#define _COMMON_FRAMEWORK_UTILS_DEMANGLE_HPP_

#include <string>

namespace common {
    namespace framework { 
        namespace utils {

    /**
     *   Function to return the demangled_name. If demangling fails, returns mangled_name
     *   @param[in] mangled_name A NULL-terminated character string containing the name to be demangled.
     *   If demangling fails or if parameter is invalid, logs an error.
     */
    std::string demangle(const char* mangled_name);

} } } // end of namespace common::framework::utils


#endif // _COMMON_FRAMEWORK_UTILS_DEMANGLE_HPP_
