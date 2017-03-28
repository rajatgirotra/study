#include "Singleton.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace common::framework::pattern;

class A 
{
    private:
        std::string str;
        int id;
        double d;
 
        A(std::string pStr, int pId) : str(pStr), id(pId)
        {
            cout << "A::ctor" << endl;
        }

        A(std::string pStr, int pId, double pD) : str(pStr), id(pId), d(pD)
        {
            cout << "A::ctor" << endl;
        }

        virtual ~A()
        {
            cout << "A::dtor" << endl;
        }

  public:

        static A* create()
        {
            return new A("Hello", -768);
        }

        static void destroy(A* poA)
        {
            delete poA;
        }

        static A* getInstance()
        {
            return Singleton<A, A>::getInstance();
        }

        friend class SingletonFactory<A>;

        std::string getStr() const { return str; }
        int getId() const { return id; }

};

int main()
{
    cout  << A::getInstance()->getStr() << "   " << A::getInstance()->getId() << endl;
    cout  << A::getInstance()->getStr() << "   " << A::getInstance()->getId() << endl;
    return 0;
}
