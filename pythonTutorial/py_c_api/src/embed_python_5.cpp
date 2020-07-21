// You can python interactively from inside C++

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <string>
using namespace std;

/* In many Python High Level Layer API's, you will see a filename argument (const char* filename).
 * The filename is used to construct the code object and may appear in tracebacks or SyntaxError exception messages.
 * otherwise it has no relevance.
 * https://docs.python.org/3/c-api/veryhigh.html
 */

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

    PyObject* ps1 = Py_BuildValue("s", "my_python_ps1>>> ");
    PyObject* ps2 = Py_BuildValue("s", "my_python_ps2... ");
    PySys_SetObject("ps1", ps1);
    PySys_SetObject("ps2", ps2);
    auto result = PyRun_InteractiveLoop(stdin, "<stdin>");
    if(result == 0) {
        cout << "PyRun_InteractiveLoop exited successfully\n";
    } else {
        cerr << "PyRun_InteractiveLoop exited with error: " << result;
    }

    for(auto&& mem : args) {
        PyMem_RawFree(mem);
    }

    Py_XDECREF(ps1);
    Py_XDECREF(ps2);
    Py_Finalize();
}