/*
 * We'll now create a simple Integer class with overload operator functions and see how we can expose those with
 * Boost.Python
 */
#include <boost/python.hpp>
#include <iostream>
#include <cstdint>
#include <numeric>
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

    friend ostream& operator<<(ostream& os, const Integer& rhs);

    friend Integer abs(const Integer& rhs)  { return Integer(std::abs(rhs.get())); }
    friend Integer pow(const Integer& lhs, const Integer& exp) { return Integer(std::pow(lhs.get(), exp.get())); }

    operator double() const { return static_cast<double>(this->m_value); }
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

ostream& operator<<(ostream& os, const Integer& rhs) {
    os << "Integer: " << rhs.m_value;
    return os;
}

BOOST_PYTHON_MODULE(override_ext) {
    using namespace boost::python;
    class_<Integer>("Integer", "Wrapper class for 32 bit signed Integers")
            .def(init<int32_t>())
            .add_property("value", &Integer::get, &Integer::set)
            .def(self + self).def(self + int32_t())
            .def(self - self).def(self - int32_t())
            .def(self += int()).def(self -= int())
            .def(self - self)
            .def(boost::python::self_ns::str(self))
            .def(float_(self))
            .def(abs(self))
            .def(pow(self, boost::python::other<Integer>()));
}

/* That works nicely. But how about Special Python functions like
 * 1) str() --> which is like ostream& operator << (ostream&) equivalent
 * 2) abs() --> gives the absolute value
 * 3) pow() --> like std::pow
 *
 * Let's put those in too.
 *
 * Read 2_README.txt next
 */