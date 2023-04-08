// Write a program to replace all spaces in a string with %20

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
#include <cstring>
using namespace std;

void urlify(const string& in, string& out) {
    // count how much space we need for %20.
    std::uint32_t spaces{};
    std::for_each(begin(in), end(in), [&spaces] (char ch) {
       if(std::isspace(ch)) ++spaces;
    });
    out.reserve(in.size() + spaces*2); // space will be replaced by '%', '2', '0'
    for(char iter : in) {
        if(std::isspace(iter)) {
            out.insert(out.size(), "%20");
        } else {
            out.insert(out.size(),  1, iter);
        }
    }
}

int main() {
    string str{"http://www.google.com/Search Query Goes Here"};
    string url_str{};
    urlify(str, url_str);
    cout << "URLify string: " << url_str << endl;
}
