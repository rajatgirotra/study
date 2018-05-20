/*
 * Very similar to abstract, just that draw() is not pure virtual, and you want to override Shape in python.
*/
#include <boost/python.hpp>
#include <iostream>
#include <string>
using namespace std;

class Shape {
public:
    virtual ~Shape() {}

    virtual void draw();
};

void Shape::draw() {
    cout << "Shape::draw()\n" ;
}

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
    void draw() override {
        if(auto draw = this->get_override("draw")) {
            // if draw() is overridden in derived, call the overridden function, else call the base class version
            draw();
        } else {
            Shape::draw();
        }
    }

    // more boilterplate needed for non-pure virtual functions
    void default_draw() {
        this->Shape::draw();
    }
};

// Create Module and expose class.
BOOST_PYTHON_MODULE(virtual_ext) {
    using namespace boost::python;

    def("factory", factory, return_value_policy<manage_new_object>());

    // instead of exposing Shape, you expose ShapeWrap now, and expose both draw and default_draw
    class_<ShapeWrap, boost::noncopyable>("Shape").def("draw", &Shape::draw, &ShapeWrap::default_draw);
}

/* please read operator.cpp and operator.py next
 */