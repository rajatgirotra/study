// Please read call_method_3.cpp first

// The boost::python::init<> class is also very rich. The class itself takes multiple template parameters, each corresponding to a type
Basically, you have multiple c'tors

1) ctor(const char* doc = 0) // which takes a doc string
2) template<typename Keywords> c'tor(const char* doc = 0, const Keywords& kw);
   or template<typename Keywords> c'tor(const Keywords& kw, const char* doc = 0) // Just the argument position is changes.

And a function to change the default call policies
template <typename CallPolicies>
unspecified operator[](const CallPolicies& policies) const


The Keywords template argument is actually a keyword-expression that is an object that holds a sequence of one or more NTBS (Null terminated Byte Strings).
Each NTBS is a keyword-argument name and can be optionally followed by a default value.
There is a helper called "arg" used to create a keyword expression with a single keyword
class arg {
    arg(const char* name)
    template <typename T>
    arg& operator=(const T& value);
    };

so arg("x")=1.0 is an example
Also the comma operator is overloaded for this class to yield a keyword expression that holds more than one NTBS of keyword arguments.
Eg:
BPM(my_module) {
    def ("f", f, (arg("x), "y", arg("z")=1.0, arg("w")=1.0), "f __doc__ string");
};

// To the change the callPolicy, just call the [] operator on the init expression.
Eg:
BPM(my_module) {
    class_<X>("X", "X_'s docstring",
              init<int, const char*>("doc_string", arg("x")=1.0, arg("y")="Hello")[with_custodian_and_ward<1,3>()]
             )
             .def(init<double>());
};

You can also specify optional template arguments to init using boost::python::optional.
template <typename T1, typename T2, ..., typename T3>
class boost::python::optional {};
If you want to specify more than one optional template parameters for init<>, they should always go
as a single boost::python::optional<> and as the last template parameter to init<>, eg:

class_<X>("X", "doc_string for X",
          init<int, double, optional<char, bool>>(...)
          );
// The above means that c'tor can take the following args
1) int,double
2) int,double,char
3) int,double,char,bool
