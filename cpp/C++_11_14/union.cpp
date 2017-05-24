/* 
1) A union is a class type which can only hold a value in only one of its non-static members at one time.
2) That member is called the active member
3) It is undefined behavior to access non-active members. ie. only access the member which was most recently written.
   However, most compilers provide a non-standard extension to read other fields instead of the active field.
4) It can have functions, c'tor, d'tor but not virtual functions
5) It cannot derive from any class nor any class can derive from it.
6) default access level is public.
7) if any of the members of the union do not have a trivial copy/move copy ctor or trivial copy/move assignment operator, then the default copy/move copy ctor/assignment is also deleted in the union and you must explicitly define it.
8) Same as 7 holds for c'tor too.
9) A union is only as large as its largest field. The value is always stored in the same memory but accessed via different members
10) The default c'tor assigns the value to the first member. ie the first member becomes active.
11) When the members of the union do not have trivial d'tors then you must explicitly called the dtor of the active member and use the placement new syntax to make another member active.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iterator>
using namespace std;

union S {
    std::int32_t n;
    std::uint16_t s[2];
    std::uint8_t c;
};

union U {
    std::string s;
    std::vector<int> v;
    ~U() {} // need to explicitly define it; as string and vector have non trivial d'tors
};


int main() {
    S s {0x12345678};  // s.n is the active member now.
    cout << std::hex << s.n << endl;
    
    s.s[0] = 0x0011;
    cout << std::hex << s.n << endl; // Undefined behavior
    cout << s.c << endl; // Undefined behavior


    U u {"Hello World"};
    cout << u.s << endl;
    u.s.~basic_string<char>();

    new (&u.v) std::vector<int>;
    u.v.push_back(10);
    u.v.push_back(20);
    u.v.push_back(30);
    cout << std::dec;
    std::copy(u.v.begin(), u.v.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl; 
    u.v.~vector<int>();
    return 0;
}
    

