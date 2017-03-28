#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct A {
    static const unsigned int count = 0;
    A() {
        cout << "A::A" << endl;
    }

    ~A() {
        cout << "A::~A" << endl;
    }

    A(const A&) {
        cout << "A(const A&)" << endl;
    }

    A& operator=(const A&) {
        cout << "A& operator=(const A&)" << endl;
    }

    A(A&&) {
        cout << "A(A&&)" << endl;
    }

    A& operator=(A&&) {
        cout << "A& operator=(A&&)" << endl;
    }
};


int main(int argc, char *argv[])
{
    using DataType = std::vector<std::unique_ptr<A>>;
    DataType vec;

    vec.emplace_back(std::make_unique<A>());
    cout << "vec.size: " << vec.size() << endl;
    {
        auto&& x = std::move(vec[0]); // this is not moving, just that x and vec[0] are now references to the same unique_ptr. So when x goes out of scope, the d'tor in A is not called as vec[0] still lives.
        //auto x = std::move(vec[0]); // will call move c'tor of the unique_ptr class, not your class A.
        if(x)
            cout << "x is managing now\n";
        else
            cout << "x is not managing now\n";

        if(vec[0])
            cout << "vec[0] is managing now\n";
        else
            cout << "vec[0] is not managing now\n";
    }
    
    cout << "vec.size: " << vec.size() << endl;
    return 0;
}

