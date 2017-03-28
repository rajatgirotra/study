/* C++11 introduces a special for loop for iterating through a range, array or collection
 *
 * for (decl : coll)
 * {
 *     cout << decl << endl;
 * }
 *
 * The requirement is that the collection should have begin() and end() functions. If not, then atleast the global begin() and end() functions
 * must be overloaded for the container class (array, range or collection) we are trying to use.
 */

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;

int main()
{
    int arr[] {1, 2, 3, 4, 5};
    
    for(double d : {1.0, 2., 3.,  4., 5.})
    {
        cout << d << "  ";
    }

    cout << endl;
    for(int i : arr)
    {
        cout << i << "  ";
    }
    cout << endl;

    vector<int> v {12, 13, 14, 15 };
    for(auto& elem : v) //The for() will return *iterator on each iteration. Here we are taking a reference to it using auto&. So the modification is visisble in the following for() where we print them out.
        elem *= 3;
    for(const auto& elem : v)
        cout << elem << "  ";
    cout << endl;

    return 0;
}

