/*
 * To call a python function from C (a common use case when your C function accepts a callback function).
 * you will need to provide a C function first that accepts a python callable. Then call that. Let's see.
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
using namespace std;

// save the python callable function in this object
static PyObject* my_callback{};

// function to set the callback
static PyObject* set_callback(PyObject* self, PyObject* args) {
    PyObject * temp{};
    PyObject * result{nullptr};

    /*
     * https://docs.python.org/2.7/c-api/arg.html#arg-parsing
     * Refer above for the format of the second argument. 0 means store the argument as a PyObject only.
     * i.e store the real address of the argument in variable callback. a ":" means that format string has ended
     * and any string after that should be used as an exception string message if the call to ParseTuple fails
     */
    if (!PyArg_ParseTuple(args, "O:callback", &temp))
        return result;
    // make sure temp is Callable, otherwise raise a typeError
    if(!PyCallable_Check(temp)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be callable");
        return result;
    }
    Py_XINCREF(temp);
    Py_XDECREF(my_callback);
    my_callback = temp;

    // make callback
    cout  <<"Making callback\n";
    PyObject_CallObject(my_callback, nullptr); // ie call my_callback with 0 arguments. If you want to call with
    // multiple arguments use Py_BuildValue() with the correct format specifiers to build a tuple of values.

    Py_RETURN_NONE;
}

// module level function to accept a python callable
static PyMethodDef moduleMethods[] = {
        {"callback", set_callback, METH_VARARGS, "register a python callable in C code."},
        {nullptr, nullptr, 0, nullptr}
};

// MyModule init
PyMODINIT_FUNC
initspam(void) {
    PyObject* m{};
    // Init module
    m = Py_InitModule("spam", moduleMethods);
    if(!m) {
        return;
    }
}

// Here we oversimplified the make_callback step. A more complete example would be.
/*
 * 1) create another module level function which can make the call_back
 * 2) The call function itself should be more complex and accept both positional and keyword arguments.
 *    2.a) positional and keyword arguments should be built with Py_BuildValue()
 *    2.b) the return value from Py_BuildValue() must be checked
 *    2.c) The PyObject* returned by Py_BuildValue() should be cleared as soon as we make the callback, even before
 *         checking the result of the callback.
 *    2.d) the result of the callback is always a PyObject* which has been incremented. So if you dont intend to use it.
 *         PY_XDECREF() it.
 *    2.e) If you intend to use it, check its return value. If the return value is NULL, return NULL from your C function
 *         so that the correct stack trace can be reported. We do all this next.
 */
