//Using an integer for the index can be some time hard to remember. MIC allows you to specify tags (ie attach a tag to
//an index) and then use the tag name to access the sequence for that index. You can specify one or more tags for an
//index.

#include "2_multi_index.hpp"
#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/tag.hpp>
#include <algorithm>

using namespace boost;
using namespace boost::multi_index;
using namespace std;

struct by_name{}; // A new tag to be used for MIC below.
struct by_sequence{}; // A new tag to be used for MIC below.

//define a MIC now.
typedef boost::multi_index_container < Employee,
            indexed_by <
                //NO TAG
                ordered_unique < identity < Employee > >,
                //WITH TAG
                ordered_non_unique < tag<by_name>, member < Employee, std::string, &Employee::name > >,
                //WITH TAG
                sequenced < tag < by_sequence> >
            >
        > EmployeeSet;

void print_by_name(const EmployeeSet& employeeSet)
{
    //SLIGHTLY MODIFIED WAY OF ACCESSING BY TAG, use index instead of nth_index.
    const EmployeeSet::index<by_name>::type& name_index = employeeSet.get<by_name>();
    cout << "Size: " << name_index.size() << endl;

    std::copy(name_index.begin(), name_index.end(), std::ostream_iterator<Employee>(cout, "\n"));
}

void print_by_id(const EmployeeSet& employeeSet) {
    std::copy(employeeSet.begin(), employeeSet.end(), std::ostream_iterator<Employee>(cout, "\n"));
}

void print_by_sequence(const EmployeeSet& employeeSet) {

    //nth_index still works even if you specify a tag
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

