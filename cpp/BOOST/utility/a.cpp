#include <iostream>
#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

class NoArg {
    public:
        bool operator() () {
            cout << "NoArg::operator()" << endl;
            return true;
        }

        int operator() (string str) {
            cout << "NoArg::operator(str):  " << str << endl;
            return -89;
        }
};

class FooClass {
    public:
        string foo(double d, int i) {
            string temp = "Double: " ;
            temp += boost::lexical_cast<string>(d);
            temp += "    Int: ";
            temp += boost::lexical_cast<string>(i);
            return temp;
        }
};

string foo(double d, int i) {
    string temp = "Double: " ;
    temp += boost::lexical_cast<string>(d);
    temp += "    Int: ";
    temp += boost::lexical_cast<string>(i);
    return temp;
}

int main() {
    boost::function0<bool> f;

    NoArg noArg;
    f = noArg;

    FooClass fc;

    /* boost::bind is a template function. */
    boost::function3<string, int, double, const char*> x = boost::bind(foo, 45.789, 78);
    //boost::function0<string> x = boost::bind(&FooClass::foo, boost::ref(fc), 45.789, 78);
    cout << x(0, 4.0, "Hello World") << endl;

 //   x = noArg;
    
}
