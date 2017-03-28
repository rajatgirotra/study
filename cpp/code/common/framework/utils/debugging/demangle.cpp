#include "demangle.hpp"
#include <cxxabi.h>
#include <common/framework/exception/exception.hpp>

using namespace common::framework::exception;

std::string common::framework::utils::demangle(const char* mangled_name)
{
    int status;
    char* realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    if(status != 0)
    {
      std::string errString;
      switch(status)
      {
          case -1 : errString = "A memory allocation failiure occurred"; break;
          case -2 : errString = "mangled_name is not a valid name under the C++ ABI mangling rules";
          case -3 : errString = "mangled_name is invalid"; break;
          default : errString = "unknown error during demangling"; break;
      }
      THROW_EXCEPTION(demangle_exception() << error_context(errString));
    }
    
    std::string demangled_name(realname);
    free(realname);
    return demangled_name;
}
