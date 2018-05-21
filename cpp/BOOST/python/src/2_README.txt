Up until now, we have mostly been returning values and accepting arguments by value. But consider the following
implementation and C++ and the associated function exposed in python

struct Y {
    X x;
    Z* z;
    Z get_value() { return z->value(); }
};

Function exposed in python:

X& foo(Y& y, Z* z) {
    y.z = z;
    return y.x;
}

in python you do:

x_obj = foo(y_obj, z);
del y_obj;
x_obj.access_something(); // CRASH here, as lifetime of x_obj is tied to lifetime of y_obj;

OR
x_obj = foo(y_obj, z);
del z;
print (y_obj.get_value())  // CRASH here, as lifetime of z in y_obj is tied to lifetime of z.

However, Python doesn't know about either case. So we can not just let python crash our C++ code so easily like this.
The way out is to use call policies. We have a number of pre-defined call policies we can use to tell Boost.python about
object lifetimes.

1) return_internal_reference<1> --> means the reference returned by a function is tied to the lifetime of the 1st argument
to that function
   Similarly, return_internal_reference<2> --> means the reference returned by a function is tied to the lifetime of the
   2nd argument to that function, and so on.

2) with_custodian_and_ward<1, 2> - is used to associate lifetimes of arguments to a function. Here it means that the lifetime
of argument 2 (the ward) is dependant on  the lifetime of the 1st argument (the custodian)

3) with_custodian_and_ward_postcall<> - We'll see usage of this and many others soon.

Remember that policies can be chained. like
policy_1<args..., policy2<args..., policy3<args...>>>

See call_policy.cpp next

