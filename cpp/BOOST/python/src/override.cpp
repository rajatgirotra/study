/*
 * We'll now create a simple Integer class with overload operator functions and see how we can expose those with
 * Boost.Python
 */
#include <boost/python.hpp>
#include <iostream>
#include <cstdint>
using namespace std;

class Integer {
    int32_t m_value;
public:
    Integer(int32_t arg = 100): m_value(arg) {}

    //getter and setter
    int32_t get() const { return m_value; }
    void set(int32_t arg) { this->m_value = arg; }

    // overload operator functions
    friend Integer operator + (const Integer& lhs, const Integer& rhs);
    friend Integer operator + (const Integer& lhs, int32_t rhs);

    Integer operator - (const Integer& rhs);
    Integer operator - (int32_t rhs) { return Integer(this->m_value - rhs);}

    Integer& operator += (int32_t rhs) {
        this->m_value += rhs;
        return *this;
    }

    Integer& operator -= (int32_t rhs) {
        this->m_value -= rhs;
        return *this;
    }

    bool operator < (const Integer& rhs) {
        return (this->m_value - rhs.get());
    }
};

Integer operator +(const Integer& lhs, const Integer& rhs) {
    return Integer(lhs.get() + rhs.get());
}

Integer operator +(const Integer& lhs, int32_t rhs) {
    return Integer(lhs.get() + rhs);
}

Integer Integer::operator - (const Integer& rhs) {
    return Integer(this->m_value - rhs.get());
}



BOOST_PYTHON_MODULE(override_ext) {
    using namespace boost::python;
    class_<Integer>("Integer", "Wrapper class for 32 bit signed Integers")
            .def(init<int32_t>())
            .add_property("value", &Integer::get, &Integer::set)
            .def(self + self).def(self + int32_t())
            .def(self - self).def(self - int32_t())
            .def(self += int()).def(self -= int())
            .def(self - self);
}

/* That works nicely. But how about Special Python functions like
 * 1) str() --> which is like ostream& operator << (ostream&) equivalent
 * 2) abs() --> gives the absolute value
 * 3) pow() --> like std::pow
 *
 * For these you can create the corresponding C++ interfaces.
 * Let's do it next.
 */