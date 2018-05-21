/*
 * Read 2_README.txt first
 */
#include <boost/python.hpp>
#include <iostream>
using namespace std;

struct X {
    int x_data;
    int get() const { return x_data; }
    void set(int arg) { this->x_data = arg; }
};

struct Z {
    int z_data;
    int value() const { return z_data; }
    void set_value(int arg) { this->z_data = arg; }
};

struct Y
{
    X x;
    Z* z;
    int z_value() { return z->value(); }
};

Y& get_Y() {
    static Y y_obj;
    y_obj.x.x_data = 100;
    return y_obj;
}

Z* get_Z_pointer() {
    Z* z = new Z();
    z->z_data = 50;
    return z;
}

X& foo(Y& y, Z* z) {
    y.z = z;
    return y.x;
}

BOOST_PYTHON_MODULE(call_policy_ext) {
    using namespace boost::python;
    class_<X>("X").add_property("data", &X::get, &X::set);
    class_<Z>("Z").add_property("value", &Z::value, &Z::set_value);
    class_<Y>("Y").def_readonly("x", &Y::x).def_readonly("z", &Y::z).def("z_value", &Y::z_value);

    // If i dont specify a call policy, Boost.Python rightly errors that i need to specify one.
    // Let me only specify one and see if i can cause a crash in call_policy.py
    def("get_Z_pointer", get_Z_pointer, return_value_policy<manage_new_object>());
    def("get_Y", get_Y, return_value_policy<reference_existing_object>());

    //def("foo", foo, return_internal_reference<1>());
    def("foo", foo, return_internal_reference<1, with_custodian_and_ward<1, 2>>());

}
