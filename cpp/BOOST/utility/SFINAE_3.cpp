/*
 * Now that you have understood the point, there is a standard way of packaging all the below.
 * Remember you always follow this coding rule.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
struct is_container
{

private:
    typedef char true_type;
    struct false_type { true_type _[2]; };

    template <typename C>
    static true_type has_iterator(typename C::iterator*);

    template <typename C>
    static false_type has_iterator(...);

public:
    static const bool value = (sizeof(has_iterator<T>(0)) == sizeof(true_type));
};

int main()
{

    cout << "Is container (int):  "<< is_container<int>::value << endl;
    cout << "Is container (vector<string>):  "<< is_container<std::vector<std::string> >::value << endl;

    return 0;
}
