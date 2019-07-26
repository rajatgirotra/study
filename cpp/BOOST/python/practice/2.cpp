/*
 * create a class that accepts a range of integers as ctor arguments. and then provide a way to iterate over that class from python.
 * Example, from python, you would do:
 *
 * range = Range(10, 20)
 * for value in range:
 *     print (value)
 *
 * To do this lets understand how iterators work in python:
 * for y in x: boils down to
 *
 * iter = x.__iter__()
 * try:
 *     while 1:
 *         y = iter.next()
 *         # play with y
 * except StopIteration:
 *     pass
 *
 * So from C++ also, we need to throw a StopIteration exception to stop the iteration.
 *
 * It turns out that all standard exceptions like std::invalid_argument, std::runtime_error, std::out_of_range etc are caught at the boundry
 * by Boost.Python itself, and mapped to appropriate exception types in python. Example: invalid_argument is ValueError.
 * For other exception types (like user defined exceptions), Boost.python converts them to PyExc_RuntimeError like
 *
 * raise RuntimeError, 'unidentifiable C++ Exception'
 *
 * the otherway in Boost.Python is to register user defined exceptions in C++ to appropriate Python exceptions like this
 *
 * struct MyUserDefinedException {};
 *
 * void translator(const MyUserDefinedException& e) {
 *     PyErr_SetString(PyExc_UserWarning, "MyUserDefinedException occurred!!");
 * }
 *
 * boost::python::register_exception_translator<MyUserDefinedException>(translator);
 *
 * Boost.Python provides a very convenient way of iterating over a C++ object. 
 * 1) Just register the function "__iter__" for your class like below
 * class_<Range>("Range").def("__iter__", boost::python::iterator<Range>());
 *
 * boost::python::iterator<T, Policies> is just a convenient way of calling
 * boost::python::range(&T::begin, &T::end)
 * 
 * boost::python::range() can take
 * 1) member functions like begin, end
 * 2) member data pointers
 * 3) adaptable function objects
 */


#include <iostream>
#include <limits>
#include <string>
#include <boost/python.hpp>
#include <iterator>
using namespace std;
namespace py = boost::python;
class Range {
    private:
	int64_t mStart {0};
	decltype(mStart) mEnd {0};
	decltype(mStart) mStep {1};

    public:
	Range(decltype(mStart) start, decltype(mEnd) end, decltype(mStep) step = 1) : mStart(start), mEnd(end), mStep(step) {}

	class iterator;
	friend class iterator;

	struct iterator {
	    using iterator_category = std::input_iterator_tag;
	    using value_type = int64_t;
	    using difference_type = int64_t;
	    using pointer = int64_t*;
	    using reference = int64_t;


	    explicit constexpr iterator(const Range& parent, value_type from) : mParent(parent), mIterValue(from) {}

	    value_type operator *() const { return mIterValue; }

	    iterator& operator ++() { 
		if(mParent.mStep > 0) {
	    	    mIterValue += mParent.mStep;
		} else {
	    	    mIterValue -= mParent.mStep;
		}
		return *this;
	    }

	    iterator operator ++(int) {
		auto iter = iterator(mParent, mIterValue);
		++(*this);
		return iter;
	    }

	    bool operator ==(const iterator& rhs) const {
		return mIterValue == rhs.mIterValue;
	    }
		    
	    bool operator !=(const iterator& rhs) const {
		return !(*this == rhs);
	    }

	    private:
		const Range& mParent;
		value_type mIterValue;
	};

	iterator begin() {
	    return iterator(*this, this->mStart);
	}

	iterator end() {
	    return iterator(*this, (mStep > 0 ? this->mEnd+1 : this->mEnd-1));
	}
};


BOOST_PYTHON_MODULE(practice_2_ext) {
    py::class_<Range>("Range", py::init<int64_t, int64_t, py::optional<int64_t>>())
	.def("__iter__", py::iterator<Range>());
}

/* in the next example, we will use range() to iterate over a fixed list of strings */

