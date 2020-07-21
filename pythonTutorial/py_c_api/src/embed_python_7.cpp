// Write an embedded python program to find the nth fibonacci number

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const std::string pycode = R"CODE(
def fib(n):
    assert n >= 0
    if n <= 1:
        return n
    else:
        return fib(n-1) + fib(n-2)

k = fib(l)

)CODE";

int main(int argc, char** argv) {
    Py_Initialize();
    if(!Py_IsInitialized()) {
        cerr << "failed to initialize python interpreter\n";
        return -1;
    }

    // Setup the __main__ module
    PyObject* main_module = PyImport_ImportModule("__main__");
    // get the dictionary of this module
    PyObject* main_dict = PyModule_GetDict(main_module);

    /* Fetch the sys module also */
    PyObject* sys_module = PyImport_ImportModule("sys");
    PyObject* sys_dict = PyModule_GetDict(sys_module);

    PyObject* version_obj = PySys_GetObject("version");
    PyObject* bytes_obj = PyUnicode_AsASCIIString(version_obj);
    auto version = PyBytes_AsString(bytes_obj);
    cout << "Python version: " << version << endl;
    Py_XDECREF(bytes_obj);
    Py_XDECREF(version_obj);

    //better way to get Python version
    cout << "Python version: " << Py_GetVersion()
         << "\nplatform: " << Py_GetPlatform()
         << "\ncopyright: " << Py_GetCopyright()
         << "\ncompiler: " << Py_GetCompiler()
         << "\nbuildinfo: " << Py_GetBuildInfo() << endl;

    /* create a variable i = 5 which will be used to call fib function */
    long l = 11;
    auto l_obj = PyLong_FromLong(l);
    PyDict_SetItemString(main_dict, "l", l_obj);

    // Run Python code
    PyRun_SimpleString(pycode.data());

    /* Extract the resultant variable, k */
    auto k_obj = PyMapping_GetItemString(main_dict, "k");
    auto k = PyLong_AsLong(k_obj);
    Py_XDECREF(k_obj);
    Py_XDECREF(l_obj);

    /* Show the result of the Python calculation */
    printf("Python calculated that fib(%d)! = %d\n", l, k);
    Py_Finalize();
}