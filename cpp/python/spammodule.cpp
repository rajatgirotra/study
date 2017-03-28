/*
We want to create a python module called spam and provide an interface to call the C library function system.
Something like:

import spam
status = spam.system("ls -l")

Historically to create a module "spam", we create a corresponding C/C++ file called "spammodule.c (or spammodule.cpp)"
Its not required but a good practice.
*/

#include <Python.h>  // this must be the first header to be included before any other headers.

static PyObject* spam_system(PyObject* self, PyObject* args);


// Lets define a list of Python method definitions, ie link python calls to corresponding C calls
static PyMethodDef SpamMethods[] = {
    { "system", spam_system, METH_VARARGS,
      "Execute a shell command"},
    {NULL, NULL, 0, NULL}
};

/* METH_VARARGS means that python should pass arguments in a way that is acceptable by PyArg_ParseTuple() */
/* it can also be METH_VARARGS | METH_KEYWORDS means that keyword arguments can also be passed to the function.
In that case, the function should accept a third PyObject* which will be a dictionary of keywords. Both second
and third arguments can be extracted using PyArg_ParseTupleAndKeywords() */

/* Lets declare a custom exception type */
static PyObject* SpamError;

PyMODINIT_FUNC // this is a macro that declares a void retrun type and also encapsulates in "extern C" if compiled using c++
initspam(void) {  // module initialization function name, should be init<ModuleName>, ie initspam in this case.
    PyObject *m;
    m = Py_InitModule("spam", SpamMethods);  // specify the name and a list of PyMethodDef, returns a PyObject represnting a python module object.
    /* We also have Py_InitModule3() which takes a const char* doc as an extra document string
       Py_InitModule4() takes two more arguments : a PyObject* which is passed as the self parameter
       to module functions you define. The last argument is an int which must be PYTHON_API_VERSION.
    */
    if (m == NULL)
        return;

    SpamError = PyErr_NewException("spam.error", NULL, NULL);
    Py_INCREF(SpamError);
    PyModule_AddObject(m, "error", SpamError);
}
/* When you say "import spam", initspam will be called, the module will be added to sys.modules under the name "spam" 
 */

// Next we write a static function which will be called when spam.system() is called from python
static PyObject* spam_system(PyObject* self, PyObject* args) {
    const char* command;
    int status;

    if (!PyArg_ParseTuple(args, "s", &command)) {
        return nullptr;
    }
    status = system(command);
    if (status != 0) {
        PyErr_SetString(SpamError, "System command failed");
        return nullptr;
    }
    return Py_BuildValue("i", status);
}

/*
For functions like these which are written at file scope, the argument self is either NULL pointer or a valid pointer to a value choosen when initializing the module (using Py_InitModule4()). The second arguments args is a tuple of arguments. It is a Python object which has to be converted to corresponding C values and PyArg_ParseTuple does that.
PyArg_ParseTuple() in this case does pointer assignment (you can see that command is declared as const char*).
The second argument to ParseTuple() is "s" indicating that args contains a single string. This argument basically specifies the format of the args argument and converts and stores in command. Returns true on success, false on error.

For Functions returning void, say
return Py_RETURN_NONE;
Py_RETURN_NONE is a macro which does:
Py_INCREF(Py_None);
return Py_None;
*/



/* NOte that if however you are embedding python, then initspam() is not automatically called. unless there is an entry in the _PyImport_Inittab table
   In that case, you need to call it after calling Py_Initialize();
*/
int main(int argc, char* argv[]) {
    Py_SetProgramName(argv[0]);

    Py_Initialize();

    initspam();
}

/*
You can built the python package using:
gpp -I /path/to/python -fPIC -c spammodule.cpp
gpp --shared -fPIC spammodule.o -o spammodule.so
export PYTHONPATH=.
python
>> import spam
>> spam.system("ls -l"
>> quit()
*/
 
