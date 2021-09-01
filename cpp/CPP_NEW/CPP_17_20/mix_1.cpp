#include <iostream>
#include <map>
using namespace std;

int main()
{
    // create a map<string, int>
    std::map<string, int> namesMap { {"Rajat", 38}, {"Vidhu", 36} };

    // create a map copy. C++17 can now deduce template arguments for class templates from the initializer
    std::map mapCopy (namesMap);

    // try to update Rajat's age to 40 using std::map::insert_or_assign
    // C++17 now allows declaring variables visible in the scope of the if statement only (called init-if)
    // auto [iter, wasAdded] = mapCopy.insert_or_assign("Rajat", 40) --> using structured bindings
    if(auto [iter, wasAdded] = mapCopy.insert_or_assign("Rajat", 40); !wasAdded)
        cout << iter->first << " reassigned...\n";
    else {
        // wasAdded can be accessed here also.
        cout << iter->first << " inserted...\n";
    }

    // output map key values using structure bindings
    for (auto&& [key, value] : mapCopy) {
        cout << key << " is " << value << endl;
    }
}
