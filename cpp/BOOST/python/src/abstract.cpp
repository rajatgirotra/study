/*
 * What would happen when you want to expose an abstract base class in python? There are multiple use cases possible
 * 1) The derived class which overrides the pure virtual function is written in C++ and to be exposed to python
 * 2) The derived class which overrides the pure virtual function is to be written in python.
 * 3) The derived class which overrides the pure virtual function is to be written in python, and the pure virtual
 * function will be called from C++.
 *
 * For ABC's we need to write some boilerplate code. Let's see.
*/
#include <boost/python.hpp>
#include <iostream>
#include <string>
using namespace std;

class Shape {
public:
    virtual ~Shape() {}

    virtual void draw() = 0;
};

class Square : public Shape {
public:
    void draw() {
        cout << "Square::draw()\n";
    }
};

// module level factory method to return an instance of shape
Shape* factory() {
    return new Square();
}

// Boilerplate, create an extra class which derives from Shape and boost::python::wrapper
class ShapeWrap : public Shape, public boost::python::wrapper<Shape> {
public:
    // Override the virtual function and call get_override() in it.
    void draw() {
        this->get_override("draw")();
    }
};

// Create Module and expose class.
BOOST_PYTHON_MODULE(abstract_ext) {
    using namespace boost::python;

    def("factory", factory, return_value_policy<manage_new_object>());

    // instead of exposing Shape, you expose ShapeWrap now
    class_<ShapeWrap, boost::noncopyable>("Shape").def("draw", pure_virtual(&Shape::draw));
    // pure_virtual tells Boost.Python that draw is pure virtual.
    //boost::noncopyable is actually the 4th template parameter. But class_ template parameters are special in the
    // sense that you can pass them in any order. Here non_copyable only means that ShapeWrap objects will be suppressed
    // from to_python() conversions which copies instances. We'll see later what this really means.
}

// Read abstract.py and virtual.cpp next
