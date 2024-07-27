#include <iostream>
#include <string>
#include <set>
#include <array>
#include <chrono>
using namespace std;
using namespace std::literals;

std::set<std::string> namesSet;

std::array<std::string, 5> namesArr {"Rajat", "Vidhu", "Myra", "Viraj", "Shweta"};

// function taking universal reference to add names to the namesSet
template <typename T>
void addName(T&& arg) {
     auto now = std::chrono::steady_clock::now().time_since_epoch().count();
     cout << "addName(T&& args) called at: " << now << ", adding: " << arg << " to set\n";
     namesSet.insert(std::forward<T>(arg));
}

void addName(size_t index) {
    addName(namesArr.at(index));
}

int main() {
//    unsigned short s = 1;
    size_t s = 1;
    addName(s); // this will try to invoke the universal reference instead of the int version as short required promotion to int.

    for(auto&& name : namesSet) {
        cout << "Name: " << name << endl;
    }
}

/* Use tag dispatching and add a second parameter to the addName() function for integral and non-integral types. */
