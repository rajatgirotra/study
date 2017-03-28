/*
 * Depending on the collection type you are using, some of the collection types can also take a functor on how to sort or order the 
 * elements in the collection. Same as you do in std::set or std::map (remember KeyComp = std::less<T> etc etc)
 *
 * By default it is std::less<T>
 *
 * We have the following requirements for which we use bimaps.
 *
 * 1) We want to store a list of countries and corresponding populations.
 * 2) We want to retrieve the countries list based on population in decreasing order.
 * 3) Given a country we need to fetch its population.
 */

#include <iostream>
#include <string>
#include <cassert>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <map>

using namespace std;
using namespace boost::bimaps;
using namespace boost;

template <typename MapType>
void printRM(const MapType& m)
{
    typedef typename MapType::const_iterator Iterator;
    for(Iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        cout << "Country: " << iter->second << "   Population: " << iter->first << endl;
    }
}

int main()
{
    typedef boost::bimap <
        unordered_set_of <std::string>, // We dont need any order on the country list. You use an ordered set for faster lookup.
        multiset_of <unsigned long, std::greater<unsigned long> > // Two countries can have the same population so using multimap.
                                                                // std::greater to sort in decreasing order
        > bimap_type;

    bimap_type bm;

    //Populate with countries and population
    typedef bimap_type::value_type relation;
    bm.insert(relation("Cayman Islands", 57570));
    bm.insert(relation("Germany", 80425823));
    bm.insert(relation("Sierra Leone", 5978727));
    bm.insert(relation("Turks and Caicos Islands", 32427));
    bm.insert(relation("Zambia", 14075099));
    bm.insert(relation("India", 1236686732));

    //Print country list based on population in decreasing order.
    printRM(bm.right);

    long population = bm.left.find("Germany")->second;
    cout << "Population of Germany is: " << population << endl;

    return 0;
}
