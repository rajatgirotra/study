/*
 * SFINAE - Substitution failure is not an error
 * This can be described as the compiler's process of eliding from the overload resolution set, ANY template where a
 * type subsitution error would occur. Lets see an example.
 */

#include <iostream>
#include <string>

using namespace std;

int getNegative(const int& roInt)
{
    return -roInt;
}

template <class T>
typename T::result_type getNegative(const T& t)
{
    return -t();
}


int main()
{
    cout << getNegative(10) << endl;
    return 0;
}

/*
 * The compiler will generate a template version of getNegative but because
 * int::result_type does not exist, it will be removed from the overload resolution set.
 * So the simple getNegative() function is called.
 *
 */
