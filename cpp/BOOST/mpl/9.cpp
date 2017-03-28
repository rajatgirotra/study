/*
 * Here we look at different types of type_traits defined in boost
 */

#include <iostream>
#include <boost/type_traits.hpp>
#include <string>

using namespace std;

struct A{};
class B {};
union U {
    char ch[10];
    int u;
};

enum myEnum { RED, GREEN, BLUE } enumObj;

int main()
{
    cout << boolalpha << "is array (int[]): " << boost::is_array<int[]>::type::value << endl;
    cout << boolalpha << "is array (int[][6]): " << boost::is_array<int[][6]>::type::value << endl;
    cout << boolalpha << "is array (int*): " << boost::is_array<int*>::type::value << endl;

    cout << endl;
    cout << "is class (struct{}): " << boost::is_class<A>::type::value <<endl;
    cout << "is class (class{}): " << boost::is_class<B>::type::value <<endl;
    cout << "is class (union{}): " << boost::is_class<U>::type::value <<endl;

    cout << endl;
    cout << boolalpha << "is enum (myEnum): " << boost::is_enum<myEnum>::type::value << endl;
    cout << boolalpha << "is enum (int): " << boost::is_enum<int>::type::value << endl;

    cout << endl;
    cout << boolalpha << "is float (float): " << boost::is_float<float>::type::value << endl;
    cout << boolalpha << "is float (long double): " << boost::is_float<long double>::type::value << endl;
    cout << boolalpha << "is float (long): " << boost::is_float<long>::type::value << endl;

    cout << endl;
    cout << boolalpha << "is reference (float&): " << boost::is_reference<float&>::type::value << endl;
    cout << boolalpha << "is reference (long double): " << boost::is_reference<long double>::type::value << endl;
    cout << boolalpha << "is reference (A&): " << boost::is_reference<A&>::type::value << endl;
    cout << boolalpha << "is reference (B*): " << boost::is_reference<B*>::type::value << endl;

    cout << endl; 
    /*
     *  is_function<int (void)>::type::value returns true.
     *  is_function<long (double, int)>::type::value return true.
     *  is_function<long (*)(double, int)>::value is false as it is pointer to function.
     *  is_function<long (&)(double, int)>::value is false as it is a reference to a function.
     *  is_function<long (MyClass::*)(double, int)>::value is false as it is a pointer to a member function.
     */

     /* Similarly you have
      * is_pointer<T>, is_reference<T>, is_void<T>, is_member_pointer<T> etc etc.
      */

     /* Then there are some more type traits like.
      * is_arithmetic<T>, is_compound<T>, is_fundamental<T> etc etc..
      * Most of these type traits are boolen expressions but we have a category of meta-functions that apply
      * transformations of type.*/

    /* For example, remove_const<T>, remove_volatile<T>, remove_cv<T>, add_pointer<T>, remove_pointer<T>,
     * add_reference<T>, remove_reference<T>, remove_bounds<T> etc etc. These expressions basically perform 
     * arithmetic on types. */

     /* In boost type_traits library all meta functions which yield a boolean result have a nested boolean type ::value
      * and all meta functions with a type result (ie which perform transformation) have a nested type  ::type 
      */

    return 0;
}

