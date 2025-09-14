/*
 * boost::fusion is just like std::pair<> but for types. In std::pair<> both key and values are runtime objects.
 * However, in fusion::pair<> key is a compile type object (mostly an empty class like a tag class).
 * The value is a runtime object. We use it with fusion::map<> like containers.
 */
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/mp11/list.hpp>
#include <iostream>
#include <string>
#include <boost/type.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/algorithm.hpp>

namespace fusion = boost::fusion;
using namespace std;
namespace mp11 = boost::mp11;

struct name_key {};
struct age_key {};
struct city_key {};

template <typename T>
void print() {
    cout << __PRETTY_FUNCTION__ << endl;
}

int main() {
    using namePair_t = fusion::pair<name_key, std::string>;
    namePair_t name("Rajat");
    using agePair_t = fusion::pair<age_key, size_t>;
    agePair_t age(42);
    using cityPair_t = fusion::pair<city_key, std::string>;
    cityPair_t city("New Delhi");

    fusion::map<
        namePair_t, agePair_t, cityPair_t
        > person(name, age, city);

    cout << fusion::at_key<city_key>(person) << endl;
    print<agePair_t::first_type>();
    print<agePair_t::second_type>();

    /*
     * boost mp_product<> takes a template type as first argument, and multiple sequences as next N arguments.
     * It produces a cartisan product from each element in the N sequences and use that to create objects of the first argument type.
     * so return type is an mp11::mp_list<FirstArgumentType...> where sizeof...(this mp_list) is sizeof(N)
     * example:
     */
    using List1_t = mp11::mp_list<int, double>;
    using List2_t  = mp11::mp_list<string, bool>;
    using List3_t = mp11::mp_product<fusion::pair, List1_t, List2_t>;
    print<List3_t>();

    //mp_rename converts the base class of the template parameters.
    using Renamed_t = mp11::mp_rename<List3_t, fusion::map>; // base class converted from mp_list to fusion::map
    print<Renamed_t>();
    Renamed_t renamed;
    fusion::at_key<int>(renamed) = "Hello World!";
}