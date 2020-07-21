#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

/* any python extension (ie module) you write must have a module init function. the init function MUST be
 * PyInit_<moduleName>. This module init function MUST create a module object using PyModule_Create(PyModuleDef*).
 * PyModule_Create(PyModuleDef*) returns a PyObject* representing this python module.
 * You can also do other initialization related work in the init function. Like creating a new Exception class for your module. etc.
 *
 * But what is PyModuleDef? PyModuleDef is just a data structure holding all the information needed to create the module object.
 * PyModuleDef has a variable PyMethoDef*. PyMethodDef* is a data structure which defines the methods/functions available in your module.
 *
 * So first we will define a module method "system" which runs the system() C api. and them we will create PyMethodDef, PyModuleDef, PyInit_spam
 */

static PyObject* spam_error {}; // a PyObject* representing an exception object that we create later.


// Creating a function at global scope will create a module level function in python.
// self refers to the module instance, and args refer to the arguments passed to system.
// if the function was inside a class, self would refer to the class instance.
// args refers to a tuple object containing the positional arguments passed to this function.
static PyObject* spam_system(PyObject* self, PyObject* args) {
    const char* command {};
    // convert args Python tuple to const char*
    int ret {};
    // The strings in the argument are also Python objects, So we need to translate them into C objects.
    // see https://docs.python.org/3/c-api/arg.html on details on PyArg_ParseTuple()
    // Typically all Python API's return >=0 for success and -1/NULL for failure.
    // PyArg_ParseTuple() is an exception to this rule.
    if(!PyArg_ParseTuple(args, "s", &command)) // return True on Success, false on failure.
      return nullptr;
    ret = system(command);
    if(ret != 0) {
        PyErr_SetString(spam_error, "system command failed");
        return nullptr;
    }

    // Free the memory buffer after we are done with it
    PyMem_Free(const_cast<char*>(command));
    return PyLong_FromLong(ret);
}

static struct PyMethodDef spam_methods[] {
    // method_name (const char*), pointer to C implementation, integer flags(METH_VARARGS|METH_KEYWORDS), doc string (const char*)
        {"system", spam_system, METH_VARARGS, "Executes a shell command."},
        {nullptr, nullptr, 0, nullptr} // MUST ALWAYS BE THE LAST SENTINAL
};

static struct PyModuleDef spam_module {
        PyModuleDef_HEAD_INIT, // ALWAYS THIS
        "spam", // module name
        nullptr, // module documentation.
        -1,
        spam_methods
};

PyMODINIT_FUNC PyInit_spam(void) {
    // we will create a module object and a new exception type for our module.
    PyObject* module_object = PyModule_Create(&spam_module);
    if(!module_object) {
        return module_object;
    }

    // module object created. continue initialization. let's create our new exception object
    spam_error = PyErr_NewExceptionWithDoc("spam.error", "exception class for our spam module", nullptr, nullptr);
    Py_XINCREF(spam_error); // never decref it. This will make sure, the exception object is never deallocated.

    // add the exception to your module using PyModule_AddObject(). you will use this function very often in module initialization.
    if(PyModule_AddObject(module_object, "error", spam_error) != 0) {
        Py_CLEAR(spam_error);
        Py_DECREF(module_object);
        module_object = nullptr;
    }

    return module_object;
}