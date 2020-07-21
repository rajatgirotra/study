/*
 * Same as embed_python_1.cpp but we wrap the char* in std::unique_ptr
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <memory>
using namespace std;

namespace {
    auto free_py_memory = [] (void* p) { PyMem_Free(p); };
}

int main(int argc, char** argv) {
    Py_Initialize();
    if(!Py_IsInitialized()) {
        cerr << "unable to initialize python interpreter\n";
        return -1;
    }
    cout << "Python interpreter initialized\n";
    // get Python interpreter name and get sys.path
    {
        using PythonMemoryPtr = std::unique_ptr<char, decltype(free_py_memory)>;
        auto program_name = Py_GetProgramName(); // returns wchar_t*, need to convert to char* using Py_EncodeLocale(), the char* needs to be free'd later using PyMem_Free(void* p)
        PythonMemoryPtr program_name_ascii(Py_EncodeLocale(program_name, nullptr), free_py_memory);

        auto program_full_path = Py_GetProgramFullPath();
        PythonMemoryPtr program_full_path_ascii(Py_EncodeLocale(program_full_path, nullptr), free_py_memory);

        auto prefix = Py_GetPrefix();
        PythonMemoryPtr prefix_ascii(Py_EncodeLocale(prefix, nullptr), free_py_memory);

        auto exec_prefix = Py_GetExecPrefix();
        PythonMemoryPtr exec_prefix_ascii(Py_EncodeLocale(exec_prefix, nullptr), free_py_memory);

        auto path = Py_GetPath();
        PythonMemoryPtr path_ascii(Py_EncodeLocale(path, nullptr), free_py_memory);

        cout << "Program Name: " << program_name_ascii.get() << endl;
        cout << "Program Full Path: " << program_full_path_ascii.get() << endl;
        cout << "Prefix: " << prefix_ascii.get() << endl;
        cout << "Exec Prefix: " << exec_prefix_ascii.get() << endl;
        cout << "Path: " << path_ascii.get() << endl;
    }
    Py_FinalizeEx();
}
