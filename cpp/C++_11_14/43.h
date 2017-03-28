// Copyright (C) 2015 by RajatGirotra
#pragma once

#include <iostream>
#include <type_traits>
#include <string>
#include <typeinfo>
#include <cxxabi.h>
using std::cout;
using std::string;
using std::endl;
/*
is_copy_assignable<T>::value::type
True if copy assignment function is defined - either implicitly or explicitly
always True for scalar types

is_copy_constructible<T>::value::type
True if copy constructor function is defined - either implicitly or explicitly
always True for scalar types

is_default_constructible<T>::value::type
True if default constructor is available and always True for scalar types.

is_move_assignable<T>::value::type - 
  True if move assignment operator is defined - or if a copy assignment operator
is available to be called for rvalue references. (which is always the case except when
the move assignment operator is  deleted). Will explore more next

is_more_constructible - 
  True if move constructor is defined - or if a copy construtor 
is available to be called for rvalue references. (which is always the case except when
the move constructor is  deleted). Will explore more next
This means that all copy-constructible types are move constructible

*/

std::string demangle(const char* mangled_name) {
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

#define IS_CONSTRUCTIBLE(A, x)\
    "std::is_constructible<" << x <<"> : "<<std::is_constructible<A>::value<<endl

#define IS_DEFAULT_CONSTRUCTIBLE(A, x)\
    "std::is_default_constructible<" << x <<"> : "<<std::is_default_constructible<A>::value<<endl

#define IS_COPY_CONSTRUCTIBLE(A, x)\
    "std::is_copy_constructible<" << x <<"> : "<<std::is_copy_constructible<A>::value<<endl

#define IS_COPY_ASSIGNABLE(A, x)\
    "std::is_copy_assignable<" << x <<"> : "<<std::is_copy_assignable<A>::value<<endl

#define IS_MOVE_ASSIGNABLE(A, x)\
    "std::is_move_assignable<" << x <<"> : "<<std::is_move_assignable<A>::value<<endl

#define IS_MOVE_CONSTRUCTIBLE(A, x)\
    "std::is_move_constructible<" << x <<"> : "<<std::is_move_constructible<A>::value<<endl


template <typename T>
void print_type_traits() {
    std::cout << endl;
    std::cout << std::boolalpha;
    string name = demangle(typeid(T).name());
    //std::cout << IS_CONSTRUCTIBLE(T, name);
    std::cout << IS_DEFAULT_CONSTRUCTIBLE(T, name);
    std::cout << IS_COPY_CONSTRUCTIBLE(T, name);
    std::cout << IS_COPY_ASSIGNABLE(T, name);
    std::cout << IS_MOVE_CONSTRUCTIBLE(T, name);
    std::cout << IS_MOVE_ASSIGNABLE(T, name);
    std::cout << std::endl;    
}
