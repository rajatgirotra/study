/* Let say you have a class which encapsulates some data structure with many elements and has a getter that returns the data structure by value.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

struct SomeDataStructure {
    SomeDataStructure() = default;
    SomeDataStructure(const SomeDataStructure&) {
        cout << "SomeDataStructure Copy Ctor" << '\n';
    }
    SomeDataStructure(SomeDataStructure&&) {
        cout << "SomeDataStructure Move Ctor" << '\n';
    }
};
    

class Widget {
private:
    using DataType = SomeDataStructure;
    DataType values;

public:
    DataType& getValues() {
        return values;
    }

    // DataType& getValues() & {
    //     return values;
    // }

    // DataType getValues() && {
    //     return std::move(values);
    // }
};

Widget makeWidget() {
    return Widget();
}

int main() {
    Widget w;
    // w.getValues().push_back(100.3);

    // std::copy(w.getValues().begin(), w.getValues().end(), ostream_iterator<double>(cout, "\n"));

    auto val1 = w.getValues(); // getValues() returns lvalue reference which is an lvalue, so according to the standard, the copy c'tor of vector will be invoked.

    auto val2 = makeWidget().getValues(); // same as above. Even though widget is temporary, copy'ctor of vector will be called. We can improve this by stating that when getValues() is called with an rvalue, return vector by value (ie we should return an rvalue when Widget is an rvalue). We can do this by using reference qualifiers 
    return 0;
}

/*
  Run it, then uncomment the reference qualifier versions and comment the normal one. The rerun and compare output */
