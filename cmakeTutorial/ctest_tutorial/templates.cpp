//
// Created by rajatgirotra on 6/3/18.
//

#include <iostream>
#include <string>
#include <cxxabi.h>
#include <typeinfo>
using namespace std;

string demangle(const char* mangled_name) {
  char* realname {};
  int status = 0;
  realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
  std::string returnStr(realname);
  free(realname);
  return returnStr;
}

template <typename T, int ARR_SIZE=10>
struct Fifo {
  T t;

  string typeT() const {
    return demangle(typeid(T).name());
  }
};

template <int* PO>
struct NonType {

  string typeT() const {
    return demangle(typeid(PO).name());
  }
};

int arr[10];

int main() {
  Fifo<double[32], 10> f;
  cout << sizeof(f) << endl;
  cout << demangle(typeid(f).name()) << endl;
  cout << f.typeT() << endl;

//  int arr[10];
  NonType<arr> nt;
  cout << sizeof(nt) << endl;
  cout << demangle(typeid(nt).name()) << endl;
  cout << nt.typeT() << endl;
}