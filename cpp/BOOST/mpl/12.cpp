/* Same as 11.cpp but i will try to do type checking to see if T is a reference or not.
 * Test yourself
 * Write a metafunction add_const_ref<T> which returns T if T is a reference type.
 * Otherwise it returns T const&.
 */

#include <iostream>
#include <boost/type_traits.hpp>
using namespace std;

//I know I am not doing any checking here if parameter T is a reference type or not
//But out of magic all my test cases are passing.
template <typename T, bool is_const_ref>
struct add_const_ref_impl;

template <typename T>
struct add_const_ref_impl<T, false>
{
    typedef const T& type;
};

template <typename T>
struct add_const_ref_impl<T, true>
{
    typedef T type;
};
    
template <typename T>
struct add_const_ref
{
    typedef typename add_const_ref_impl<T, boost::is_reference<T>::value>::type type;
};

int main()
{
    //Test 1.
    int a = 10;
    add_const_ref<int>::type b = a;
    a++;
    cout << b << endl; //should be 11.
    cout << boolalpha << boost::is_same<int, add_const_ref<int>::type>::value << endl;

    //Test 2.
    cout << endl;
    int* poInt = new int(20);
    add_const_ref<int*>::type refToPointer = poInt;
    (*poInt)++;
    cout << *refToPointer << endl; //should be 21.
    cout << boolalpha << boost::is_same<int*, add_const_ref<int*>::type>::value << endl;

    //Test 3.
    cout << endl;
    int x = 100;
    int& y = x;
    add_const_ref<int&>::type newRefToY = y;
    x--;
    cout << newRefToY << endl; // should be 99.
    cout << boolalpha << boost::is_same<int&, add_const_ref<int&>::type>::value << endl;

    //Test 4.
    cout << endl;
    const int i = 99;
    add_const_ref<const int>::type constRefToI = i;
    cout << constRefToI << endl; //should be 99.
    cout << boolalpha << boost::is_same<const int, add_const_ref<const int>::type>::value << endl;

    //Test 5.
    cout << endl;
    const int i2 = 999;
    const int& constRefToI2 = i2;
    add_const_ref<const int&>::type anotherConstRefToI2 = constRefToI2;
    cout << anotherConstRefToI2 << endl; //should be 999.
    cout << boolalpha << boost::is_same<const int&, add_const_ref<const int&>::type>::value << endl;

    return 0;
}
