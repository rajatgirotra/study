// fusion::cons is a data structure in fusion. It is a recursive list data structure. This means it contains a value and then a link
// to another cons data structure. Something like fusion::cons<int, cons<float>>
// the cons data structure is inspired from lisp. Lisp has a similar data strcuture and two common operations (car and cdr).
// car returns the element at the front of the list and cdr returns everything after the first element.
// This is how boost fusion declares it.
// template <typename Car, typename Cdr = nil>
// struct cons;
#include <cxxabi.h>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/mpl/int.hpp>
#include <iostream>
#include <string>
#include <cassert>
using std::cout;
using std::cin;
using std::endl;
using std::string;
namespace fusion = boost::fusion;
namespace mpl = boost::mpl;

string demangle(const char* mangled_name) {
    int status = -1;
    char* realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    if (status == 0) {
        string result(realname);
        free(realname);
        return result;
    } else {
        string result(mangled_name);
        return result;
    }
}

struct print_xml {
    template <typename Type>
    void operator() (const Type& t) const {
        cout << "<" << demangle(typeid(t).name()) << ">"
             << t << "</" << demangle(typeid(t).name()) << ">" << endl;
    }
};

int main() {
    fusion::cons<int> c{}; // car will be 0 and cdr will be fusion::nil_
    // Fetch car of cons
    cout << fusion::at<mpl::int_<0>>(c) << endl;

    fusion::cons<int> nul(10);
    cout << fusion::at_c<0>(nul) << endl;
}

/*
If you look at deque<> data strcuture it is similar to list. The difference is not in the data structures but the
iterators to it. Deque has a bidirectional iterator which supports prior.
List has a forward iterator.
Similarly vector has Random access iterator and supports at_c<C> and at<M>
*/
