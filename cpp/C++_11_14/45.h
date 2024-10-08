#include <iostream>
#include <string>
#include <typeinfo>
#include <cxxabi.h>
#include <cstdio>
#include <cstdlib>
using std::cout;
using std::endl;
using std::string;

static std::string demangle(const char* mangled_name) {
    int status;
    char* realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    if (status != 0) {
      std::string errString;
      switch (status) {
          case -1 : errString = "A memory allocation failiure occurred"; break;
          case -2 : errString = "mangled_name is not a valid name under the C++ ABI mangling rules";
          case -3 : errString = "mangled_name is invalid"; break;
          default : errString = "unknown error during demangling"; break;
      }
    }

    std::string demangled_name(realname);
    free(realname);
    return demangled_name;
}

