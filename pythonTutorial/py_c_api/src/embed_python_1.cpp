/*
 * We will embed python in our app and print the values of python interpreter name and sys.path
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    Py_Initialize();
    if(!Py_IsInitialized()) {
        cerr << "unable to initialize python interpreter\n";
        return -1;
    }
    cout << "Python interpreter initialized\n";
    // get Python interpreter name and get sys.path

    auto program_name = Py_GetProgramName(); // returns wchar_t*, need to convert to char* using Py_EncodeLocale(), the char* needs to be free'd later using PyMem_Free(void* p)
    auto program_name_ascii = Py_EncodeLocale(program_name, nullptr);

    auto program_full_path = Py_GetProgramFullPath();
    auto program_full_path_ascii = Py_EncodeLocale(program_full_path, nullptr);

    auto prefix = Py_GetPrefix();
    auto prefix_ascii = Py_EncodeLocale(prefix, nullptr);

    auto exec_prefix = Py_GetExecPrefix();
    auto exec_prefix_ascii = Py_EncodeLocale(exec_prefix, nullptr);

    auto path = Py_GetPath();
    auto path_ascii = Py_EncodeLocale(path, nullptr);

    cout << "Program Name: " << program_name_ascii << endl;
    cout << "Program Full Path: " << program_full_path_ascii << endl;
    cout << "Prefix: " << prefix_ascii << endl;
    cout << "Exec Prefix: " << exec_prefix_ascii << endl;
    cout << "Path: " << path_ascii << endl;

    // Need to free up memory for all these python variables.
    PyMem_Free(program_name_ascii);
    PyMem_Free(program_full_path_ascii);
    PyMem_Free(prefix_ascii);
    PyMem_Free(exec_prefix_ascii);
    PyMem_Free(path_ascii);

    Py_FinalizeEx();
}
