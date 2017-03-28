/*
 * Demonstrate use of variadic template class
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
using namespace std;

template <typename T, typename... _ConstructorArgs>
class VariadicClass
{

    static const uint32_t size = sizeof...(_ConstructorArgs); // --> Note this line.
    static_assert(size < 4, "We do not support more than four c'tor arguments"); 

    public:
        VariadicClass()
        {
            cout << "VariadicClass::VariadicClass()" << endl;
        }

        VariadicClass(int, char, bool);
        VariadicClass(double, vector<string>);
};

template <typename T, typename... _ConstructorArgs> // --> Note this line
VariadicClass<T, _ConstructorArgs...>::VariadicClass(int, char, bool) // --> Note this line.
{
    cout << "VariadicClass::VariadicClass(int, char, bool)" << endl;
}

template <typename T, typename... _ConstructorArgs>
VariadicClass<T, _ConstructorArgs...>::VariadicClass(double, vector<string>)
{
    cout << "VariadicClass::VariadicClass(double, vector<string>)" << endl;
}

int main()
{
    VariadicClass<int> v1;
    VariadicClass<double, int, char, bool> v2(1, 'A', true);
    VariadicClass<double, double, vector<string>> v3(23.4, vector<string>());

    VariadicClass<double, int, char, bool, bool> v4(1, 'A', true);

    return 0;
}
