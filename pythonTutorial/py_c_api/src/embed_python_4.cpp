// same as embed_python_3.cpp but uses Py_Main(argc, wchar_t* argv)

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
    Py_Initialize();
    if(!Py_IsInitialized()) {
        cerr << "failed to initialize python interpreter\n";
        return -1;
    }

    // Remember Py_Initialize() doesnt set sys.argv
    wchar_t* args[argc];
    for(int i = 0; i < argc; ++i) {
        args[i] = Py_DecodeLocale(argv[i], nullptr);
    }
    auto result = Py_Main(argc, args);
    if(result == 0) {
        cout << "Py_Main exited successfully\n";
    } else {
        cerr << "Py_Main exited with error: " << result;
    }

    for(auto&& mem : args) {
        PyMem_RawFree(mem);
    }
    Py_Finalize();
}