#include "json_serialization.hpp"
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/adapted.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

namespace fusion = boost::fusion;
namespace mpl = boost::mpl;
using std::string;

struct Inner : public json<Inner> {
    int a;
    double b;
    bool c;

    typedef std::vector<int> vec_t;
    vec_t d;
};

struct Outer : public json<Outer> {
    int one;
    double two;
    bool three;
    
    typedef Inner array_t[2];
    array_t array;

    typedef std::set<int> set_t;
    set_t s;

    typedef std::map<int, int> map_t;
    map_t m;
};
    
/*
Use boost fusion to make the above structures as fully conforming fusion sequences.
*/
BOOST_FUSION_ADAPT_STRUCT(
    Inner,
    (BOOST_FUSION_ADAPT_AUTO, a)
    (BOOST_FUSION_ADAPT_AUTO, b)
    (BOOST_FUSION_ADAPT_AUTO, c)
    (BOOST_FUSION_ADAPT_AUTO, d)
)

BOOST_FUSION_ADAPT_STRUCT(
    Outer,
    (BOOST_FUSION_ADAPT_AUTO, one)
    (BOOST_FUSION_ADAPT_AUTO, two)
    (BOOST_FUSION_ADAPT_AUTO, three)
    (BOOST_FUSION_ADAPT_AUTO, array)
    (BOOST_FUSION_ADAPT_AUTO, s)
    (BOOST_FUSION_ADAPT_AUTO, m)
)

int main() {
    Outer o;
    o.one = 1;
    o.two = 2.2;
    o.three = false;

    o.array[0].a = 3;
    o.array[0].b = 4.4;
    o.array[0].c = true;
    o.array[0].d.push_back(11);
    o.array[0].d.push_back(22);

    o.array[1].a = 5;
    o.array[1].b = 6.6;
    o.array[1].c = false;
    o.array[1].d.push_back(33);
    o.array[1].d.push_back(44);

    o.s.insert(55);
    o.s.insert(66);

    o.m[77] = 88;
    o.m[99] = 111;

    std::cout << o.to_json();

    std::cout << std::endl;
}
