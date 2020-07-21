// embed python interpreter and call a simple python script main.py which print sys.argv ie all arguments passed to this C++ program

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

    // Remember Py_Initialize() doesnt set sys.argv. We need to do it manually.
    wchar_t* args[argc-1];
    for(int i = 1; i < argc; ++i) {
        args[i-1] = Py_DecodeLocale(argv[i], nullptr);
    }
    PySys_SetArgvEx(argc-1, args, 0);

    FILE* py_script {};
    py_script = fopen("/study/pythonTutorial/py_c_api/src/main.py", "r");

    if(py_script) {
        PyRun_SimpleFileEx(py_script, "main.py", 1);
        for(auto&& mem : args)
            PyMem_RawFree(mem);
    } else {
        cerr << "failed to open main.py.\n";
    }

    Py_Finalize();
}