// The first thing to do when using the Python API for writing modules in C/C++ is to include Python.h
// Also it must be the first header to be included.

#include <Python.h>
/* Python.h defines a number of functions, macros, variable that start with Py or PY. Those beginning with _Py
 * are only for internal use and should not be used.
 */
#include <iostream>

// Creating a function at global scope will create a module level function in python.
// spam_system internally will create a function system in module spam.
// self refers to the module instance, and args refer to the arguments passed to system.
// if the function was inside a class, self would refer to the class instance.
static PyObject* spam_system(PyObject* self, PyObject* args) {
    const char* command {};
    // convert args Python tuple to const char*
    int ret {};
    // The strings in the argument are also Python objects, So we need to translate them into C objects.
    if(!PyArg_ParseTuple(args, "s", &command)) // return True on Success, false on failure.
      return nullptr;
    ret = system(command);
    return PyLong_FromLong(ret);

    // Typically all Python API's return >=0 for success and -1/NULL for failure.
    // PyArg_ParseTuple() are exceptions to this rule.
}

// Exception Handling: As a rule of thumb, whenever a function fails, set an exception condition and return its value
// Python stores exception information globally in static variables.
// 1st variable can be NULL or NOT NULL - NOT NULL means an exception condition has occurred.
// 2nd variable stores the actual exception like KeyError, TypeError, DivideByZero error etc.
// 3rd variable stores the stack information.
// There are many PyErr_* functions available to set exceptions
// 1) PyErr_SetString() --> takes the exception object like PyExc_KeyError and the string of the error description
// 2) PyErr_SetFromErrno() --> takes the errno and constructs the error on its own using the global errno value
// 3) PyErr_SetFromObject() --> takes the exception and the associated value.
// 4) PyErr_NoMemory() --> Use this if you call malloc() directly and cannot allocate more memory.

// ALWAYS RETURN NULL or -1 WHEN A FUNCTION FAILS.

/* A function f which calls function g (which fails) should also fail and return -1 or NULL. Also it should not
 * call PyErr_() as it will overwrite the exception information created in g(); the main cause of exception.
 * You can do it if you have such a strange use case. f() can also call PyErr_Clear() which clears the global
 * exception state and does not return the error to the interpreter. You may do this if you want to handle the
 * exception totally within your program.
 */

// Read 2_spammify.cpp