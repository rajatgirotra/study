#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using namespace std;

class A {
private:
    static int iCounter;
    int id;

public:
    A() : id(++iCounter) 
    { cout << "A c'tor with id: " << id << endl; }

    A(const A&) {
        this->id = ++iCounter;
        cout << "A copy c'tor with id: " << id << endl;
    }

    ~A() {
         cout << "A d'tor with id: " << id << endl; }
};

int A::iCounter = 0;

int main()
{
    A* objA = new A();
    //boost::shared_ptr<A> aPtr (boost::make_shared<A>(objA));
    boost::shared_ptr<A> aPtr (objA);

    return 0;
}
