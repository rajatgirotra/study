#include <iostream>
#include <tuple>
#include <functional>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

class Name {
private:
    std::string firstname;
    std::string lastname;

public:
    Name(string fname, string lname) : firstname(std::move(fname)),  lastname(std::move(lname))
    {}

    friend bool operator < (const Name& lhs, const Name& rhs) {
        // std::tie is also used to do lexographi comparisons like below. Comparing two tuple compares the corresponding
        // values in the tuple.
        return std::tie(lhs.lastname, lhs.firstname) < std::tie(rhs.lastname, rhs.firstname);
    }

    friend std::ostream& operator << (ostream& os, const Name& n) {
        os << n.firstname << "  " << n.lastname << "\n";
        return os;
    }
};

int main(int argc, char* argv[]) {
    /* std::tie can be used to unpack std::pair because std::tuple has a converting assignment from pairs. */
    std::set<std::string> stringset {};
    
    bool result {};
    std::tie(std::ignore, result) = stringset.insert("HelloWorld");
    if (result) {
        cout << "first time: HelloWorld put in set" << endl;
    } else {
        cout << "first time: HelloWorld NOT put in set" << endl;
    }

    std::tie(std::ignore, result) = stringset.insert("HelloWorld");
    if (result) {
        cout << "second time: HelloWorld put in set" << endl;
    } else {
        cout << "second time: HelloWorld NOT put in set" << endl;
    }


    std::set<Name> nameset;
    nameset.emplace("Rajat", "Girotra");
    nameset.emplace("Vidhu", "Ahuja");

    //std::copy(nameset.begin(), nameset.end(), std::ostream_iterator<Name>(cout, "\t"));

    return 0;
}
