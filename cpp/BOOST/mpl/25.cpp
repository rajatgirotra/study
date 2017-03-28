#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

class A
{
public:
    template <typename U>
    void display(const U& lhs)
    {
        cout << typeid(U).name() << endl;
    }
};

template <typename DisplayWrapper, typename U>
struct Wrapper
{
    void callDisplay()
    {
        DisplayWrapper dw;
        dw.template display<U>(10);
    }
};


int main()
{
    Wrapper<A, int> w;
    w.callDisplay();
    return 0;
}   
