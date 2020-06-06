/* Here we will see how to create our own exception object. Infact any module level object is created the same way as
 * as shown below
 */

#include <Python.h>
#include <iostream>

// Create a PyObject for your user-defined exception.
static PyObject* spamError;

// module level function declaration
static PyObject* spam_system(PyObject* self, PyObject* args);

// Array of module level functions, will be used later during module initialization.
static PyMethodDef SpamMethods[] = {
        // argument 1 is the function name to be used from python
        // argument 2 is the address of the function in C
        /* argument 3 should always be METH_VARARGS or METH_VARARGS|METH_KEYWORDS
         * METH_VARARGS means you can use PyArg_ParseTuple() to parse it.
         * Use PyArg_ParseTupleAndKeywords() if arg 3 is METH_VARARGS|METH_KEYWORDS
         */
        {"system",  spam_system, METH_VARARGS, "Execute a shell command."},
        {nullptr, nullptr, 0, nullptr}        /* end Sentinel */
};

// Create your module initialization function
PyMODINIT_FUNC // nothing but extern C void
initspam(void) { // naming convention should be init<modulename>(void)
    // Create your module level object
    PyObject* m{};
    m = Py_InitModule("spam", SpamMethods); // module name is spam
    // SpamMethods is a table of functions at module level.
    //Py_InitModule() creates an entry in the sys.modules list with the name "spam"

    spamError = PyErr_NewException("spam.error", nullptr, nullptr);
    // Must increment reference count. It is possible for your module to delete an exception object.
    // in that case, the reference count will drop to 0 and the object will be garbage collected.
    // So if you try to create a new exception object, it will CRASH or give weird results.
    Py_XINCREF(spamError); // You can use Py_INCREF() too, however, PY_XINCREF() is safe if spamError is NULL.
    // So always prefer Py_XINCREF() or Py_DECREF().

    // Add object to module.
    PyModule_AddObject(m, "error", spamError);
}

static PyObject* spam_system(PyObject* self, PyObject* args) {
    const char* command {};
    int ret {};
    if(!PyArg_ParseTuple(args, "s", &command)) {
        return nullptr;
    }
    ret = system(command);
    if (ret != 0) {
        // raise spamError exception
        PyErr_SetString(spamError, "System command failed.");
        return nullptr;
    }

    //return PyLong_FromLong(ret); // or use Py_BuildValue() which is the inverse of PyArg_ParseTuple()
    return Py_BuildValue("i", ret); // build an integer return value.

    // Note: for function which have to return void, use the Py_RETURN_NONE macro
}

// Now lets try it. Just build spam.so and try to load it.
// ipython
// import spam
// spam.system('ls -ltr')
// spam.system('abcd')

// Next let's see how to call Python function from C (ie the reverse).