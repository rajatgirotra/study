// Copyright (C) 2015 by RajatGirotra
/*
  filter_if algo - Takes a pred and a sequence, and returns another sequence containing
  elements where filter_if returns mpl::true_
  template <typename Pred, typename Seq>
  filter_if<Pred>(const Seq& seq)
*/
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>

#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <cstdint>
using std::cout;
using std::endl;
using std::string;
using boost::fusion::vector;
using boost::fusion::for_each;
using boost::fusion::filter_if;
using boost::mpl::_;

// only print elements in the seq which are of pointer types.
struct print_xml {
    template <typename T>
    void operator() (const T& value) const {
        cout << "<" << typeid(value).name() << ">"
             << *value
             << "</" << typeid(value).name() << ">" << endl;
    }
};

int main(int argc, char *argv[]) {
    vector<int, double, uint64_t*> data(10, 12.25, new uint64_t(100));
    for_each(filter_if<std::is_pointer<_>>(data), print_xml());
    return 0;
}

