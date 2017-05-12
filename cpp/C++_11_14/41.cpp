// emplace_back std::vector
// what emplace_back does is that constructs the object in place at the point
// where it in inserted in the container. The way it is done is that the container
// provides an uninitialized memory space using its allocator and then uses
// placement new syntax to construct the object at that memory. Object c'tor
// parameters are passed to the emplace_back. So emplace_book takes an arbitrary
// number of parameters using variadic template.

/*
  template <typename... Args>
  void emplace_back(Args&&... args) // pass by rvalue reference to support perfect forwarding.
*/

// example below
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct President {
    std::string name;
    std::string country;
    int year;

    // c'tor
    explicit
    President(string p_name, string p_country, int p_year) :
        name(std::move(p_name)), country(std::move(p_country)), year(p_year) {
        //name(p_name), country(p_country), year(p_year) {
            cout << "I am being constructed" << endl;
            cout << "p_name" << p_name << endl;
        }

    // move c'tor
    President(President&& other) : name(std::move(other.name)),
                                   country(std::move(other.country)),
                                   year(other.year) {
        cout << "I am being moved" << endl;
    }

    // user declared assignment operator. Here you are explicitly
    // stating for the compiler to generate the default implementation
    // of the copy assignment operator.
    President& operator=(const President&) = default;
};


int main(int argc, char *argv[]) {
    std::vector<President> elections;
    std::cout << "emplace_back: "<< endl;
    elections.emplace_back("Nelson Mandela", "South Africa", 1994);

    std::cout << "\nemplace_back_2: "<< endl;
    string n {"Rajat"};
    string c {"Singapore"};
    int y {2016};
    elections.emplace_back(n, c, y);
    cout << "after emplace_back_2: n,c,y " << n << " " << c << " " <<y <<endl;

    std::cout << "\npush_back: "<< endl;
    elections.push_back(President("Pranab Mukherjee", "India", 2010));

    cout << "\nDisplaying  Now" << endl;
    for (auto& x : elections) {
        cout << "President Name: " << x.name << "  Country: "
             << x.country << "  Year: " << x.year << endl;
    }
    return 0;
}

/*
Take away:

1) emplace_back must be called with rvalues, otherwise it will behave similarly to a regular push_back.
2) The std::move in the initializer list is just for performance and has nothing to do with emplace_book.
   As a rule, start using emplace back in constructors. Please go on to read 3
3) As you can see variables n, c, y are intact even after calling emplace_back.
   This is because when emplace_back is called with lvalues, it creates copies of those objects, which get passed
    to the c'tor and it is those copies which get moved. This way after the call, the variables are have their original
   value and the call behaves exactly like push back. So AS A RULE OF THUMB, always use std::move in initializer list
   of c'tors. whether you use push_back or emplace_back.
*/
