lets look at the def() function used to wrap a C++ callable to be called from python.

template <class F>
void def(char const* name, F f);
// Very trivial - name is the name to be used in python and f is a C++ callable.

// Next to understand, what A1, A2, A3 can be, lets step back and look at some other things.

1) Easy thing first:
A1, A2, A3 can be:
a) a doc string
b) a CallPolicy or
c) keyword-expression
and can be in any order.

template <class Fn, class A1>
void def(char const* name, Fn fn, A1 const&);

template <class Fn, class A1, class A2>
void def(char const* name, Fn fn, A1 const&, A2 const&);

template <class Fn, class A1, class A2, class A3>
void def(char const* name, Fn fn, A1 const&, A2 const&, A3 const&);

2) The slightly complex thing:
boost.python provides two macros:

BOOST_PYTHON_FUNCTION_OVERLOADS(user_defined_name, function_name, min_args, max_args)
and
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(user_defined_name, member_function_name, min_args, max_args)

These macros generate a bunch of overload functions. So if you say:

void foo(int x = 1, double y = 4.25, char const* z = "wow") {
    // whatever.
    return;
}

BOOST_PYTHON_FUNCTION_OVERLOADS(my_overload, foo, 0, 3), then the macro will generate the following overloads

1) my_overload()
2) my_overload(docstring)
3) my_overload(docstring, keywords)
4) my_overload(keywords, docstring)
5) my_overload()[policies]
6) my_overload(docstring)[policies]
7) my_overload(docstring, keywords)[policies]
8) my_overload(keywords, docstring)[policies]

And then you can only use def(), with one template parameter A1, where A1 will be one of the 8 above.
Eg:

def("foo", foo,
    my_overloads("foo's docstring", arg("x"), arg("y"), arg("z"))[return_internal_reference<>()]
   );

// See not difficult at all :)
