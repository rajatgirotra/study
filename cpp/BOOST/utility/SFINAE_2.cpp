/*
 * Now we'll see how to use it using the famously known sizeof() trick.
 * Remember sizeof() is an operator that returns the size of the type which is passed as parameter.
 *
 * Let use SFINAE to check if an object has an embedded iterator type. i.e. lets see if it has ::iterator type 
 * defined.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// The approcach
// 1. typedef a type to whatever you want.
typedef char true_type;

// 2. Create another user defined type which has a different size to the one in step 1.
// Ideally always create a structure with an array of size 2 of the same type as used in step 1.
struct false_type {
    true_type _[2];
};

// 3. Create two template function overloads each returning each of the types in step 1 and step 2.
template <typename C>
true_type has_iterator(typename C::iterator*);

template <typename C>
false_type has_iterator(...);

//The thing here is that the first version will only be instantiated if our template parameter has an embedded iterator
//pointer. The second version will match always.

#define IS_CONTAINER(X) (sizeof(has_iterator<X > (0)) == sizeof(true_type))

int main()
{

    cout << "Is container (int):  "<< IS_CONTAINER(int) << endl;
    cout << "Is container (vector<string>):  "<< IS_CONTAINER(std::vector<std::string>) << endl;

    return 0;
}
