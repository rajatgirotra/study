/* How to use initialiser lists for user defined types.
 * For user defined types, C++11 has introduced a class template called std::initializer_list<>
 */

#include <cstdint>
#include <iostream>
using namespace std;

class A
{
    int a;
    int b;
    public:
        A(const int& pA, const int& pB) : a(pA), b(pB)
        {
            cout << "A::A()" << endl;
        }

        #if 1
        A(const std::initializer_list<int>& tuple) : a(0), b(0)
        {
            cout << "A::A(std::initializer_list)" << endl;
            if(tuple.size() >= 2)
            {
                auto it = tuple.begin();
                a = *it++;
                b = *it++;
            }
       }
       #endif
       
       void print() const
       {
            cout << a << "   " << b << endl;
       }
};

int main()
{
    A a(10, 20); 
    A b {10, 20};  //The std::initializer_list c'tor is preferred with this syntax.
    A c  = {10, 20};  //The std::initializer_list c'tor is preferred with this syntax.
    A d  = {10, 20, 30, 40, 50};  //The std::initializer_list c'tor is preferred with this syntax.
    a.print();
    b.print();
    c.print();
    d.print();


    return 0;
}
