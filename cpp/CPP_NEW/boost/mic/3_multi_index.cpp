#include "2_multi_index.hpp"
#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/identity.hpp>
#include <algorithm>

using namespace boost;
using namespace boost::multi_index;
using namespace std;

//define a MIC now.
typedef boost::multi_index_container < Employee,
            //Now specify the various indexes
            indexed_by <
                //1st index, sort by employee::operator<
                ordered_unique < identity < Employee > >,
                //2nd index, by less<string> on member name.
                //Note this member variable MUST BE PUBLIC, NOT PRIVATE. So we changed Employee accordingly.
                ordered_non_unique < member < Employee, std::string, &Employee::name > >,
                //3rd index, same as insertion order
                sequenced<>
            >
        > EmployeeSet;

void print_by_name(const EmployeeSet& employeeSet)
{
    //Access the MIC by index. Note Access to the index is by reference.
    //What you get back behaves like a std::multiset<> object. So you can use it as such.
    const EmployeeSet::nth_index<1>::type& name_index = employeeSet.get<1>();
    cout << "Size: " << name_index.size() << endl;

    //Output to stdout
    std::copy(name_index.begin(), name_index.end(), std::ostream_iterator<Employee>(cout, "\n"));
}

void print_by_id(const EmployeeSet& employeeSet) {
    //const EmployeeSet::nth_index<0>::type& id_index = employeeSet.get<0>();
    //What you get back behaves like a std::set<> object. So you can use it as such.
    //Output to stdout
    //std::copy(id_index.begin(), id_index.end(), std::ostream_iterator<Employee>(cout, "\n"));

    //For index 0, you really don't need to use nth_index<0>... just use the MIC directly as shown below.
    //and by default nth_index<0> is implied.
    std::copy(employeeSet.begin(), employeeSet.end(), std::ostream_iterator<Employee>(cout, "\n"));
}

void print_by_sequence(const EmployeeSet& employeeSet) {
    const EmployeeSet::nth_index<2>::type& list_index = employeeSet.get<2>();

    std::copy(list_index.begin(), list_index.end(), std::ostream_iterator<Employee>(cout, "\n"));
}

int main(int argc, char* argv[]) {
    EmployeeSet es;
    es.insert(Employee(148, "Rajat Girotra"));
    es.insert(Employee(100, "Vidhu Ahuja"));
    es.insert(Employee(200, "Shweta Sethi"));
    es.insert(Employee(248, "Jitin Sethi"));

    print_by_name(es);

    cout << endl;

    print_by_id(es);

    cout << endl;

    print_by_sequence(es);

    return 0;
}

/*
 * A multi_index_container instantiation can be declared without supplying the indexed_by part: in this case, default
 * index values are taken so that the resulting type is equivalent to a regular std::set. Concretely, the instantiation
 *
 * multi_index_container<(element)>
 *
 * is equivalent to
 *
 * multi_index_container<element,
 *     indexed_by<
 *         ordered_unique<identity<(element)> >
 *     >
 * >
 */
    

