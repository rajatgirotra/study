// A no. of support/helper functions are available in general.
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/support.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <iostream>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

using std::cout;
using std::endl;
using std::string;
using namespace boost::mpl::placeholders;
namespace mpl = boost::mpl;
namespace fusion = boost::fusion;

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
    // is_sequence<>::type returns mpl::true_ if it is a sequence type
    cout << "is_sequence<>" << endl;
    cout << std::boolalpha << boost::is_same<mpl::true_, boost::fusion::traits::is_sequence<int>::type>::value << endl;
    cout << std::boolalpha << boost::is_same<mpl::true_, boost::fusion::traits::is_sequence<fusion::vector<int>>::type>::value << endl;

    // is_view<>::type returns mpl::true_ if it is a fusion view type
    cout << "\nis_view<>" << endl;
    typedef fusion::vector<int, bool, int*, double> vector_t;
    typedef fusion::filter_view<vector_t, boost::is_integral<_>> filter_view_type;
    cout << std::boolalpha << boost::is_same<mpl::true_, boost::fusion::traits::is_view<filter_view_type>::type>::value << endl;
    cout << std::boolalpha << boost::is_same<mpl::true_, boost::fusion::traits::is_view<vector_t>::type>::value << endl;

    // tag_of --> all sequences and iterators are have internal tag type used by boost fusion to support tag dispatching.
    // meaning it uses tag values to call the correct versions of algorithms based on the tag type.
    // all list<> type should have the same tag, all vector<> types should have the same tag and soon.
    cout << "\ntag_of<>" << endl;
    typedef fusion::list<int> list_int_type;
    typedef fusion::list<int*, double*> list_int_start_double_star_type;
    cout << std::boolalpha << boost::is_same<
                                  fusion::traits::tag_of<list_int_type>::type,
                                  fusion::traits::tag_of<list_int_start_double_star_type>::type>::value << endl;

    // fusion sequences and iterators have a number of categories. category_of<> tells you the type of the category.
    // I am aware of the following category types:
    /* incrementable_traversal_tag, single_pass_traversal_tag, forward_traversal_tag, bidirectional_traversal_tag,
       random_access_traversal_tag, associative_tag, unbounded_tag */
    cout << "\ncategory_of<>" << endl;
    cout << std::boolalpha << boost::is_base_of<
                         fusion::forward_traversal_tag,
                         fusion::traits::category_of<list_int_type>::type>::value << endl;

    // deduce<>::type - See example below. Basically it removes const and reference. so const int& is deduced as int
    // it keeps array types as such, but removes the const on it. This is used in make_list() as you'll see soon.
    cout << "\ndeduce<>" << endl;
    typedef fusion::traits::deduce<const int&>::type const_int_ref_deduced_type;
    typedef fusion::traits::deduce<const char[]>::type const_char_array_deduced_type;
    cout << "const_int_ref_deduced_type: " << demangle(typeid(const_int_ref_deduced_type).name()) << endl;
    cout << "const_char_array_deduced_type: " << demangle(typeid(const_char_array_deduced_type).name()) << endl;

    // Similarly you have deduce_sequence<>::type which will do the same as deduce, but can take multiple arguments.
    cout << "\ndeduce_sequence<>" << endl;
    typedef fusion::vector<const int&, const double (&)[2]> vector_type;
    typedef fusion::traits::deduce_sequence<vector_type>::type deduced_vector_type;
    // deduced_vector_type types will be int and double[2]. I'll show later how we can iterate over each type.
}
