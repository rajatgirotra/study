/* 
   An anonymous union is one which doesnt have a name and you dont define any object, reference or pointer to it.
   An anonymous union cannot have static data members, member functions. All their members must always be public.
   The members of an anonymous union are available in the enclosing scope. If enclosing scope is namespace scope, then the union must be declared as static (or be part of an unnamed namespace)
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iterator>
using namespace std;

static union {
    int i;
    char c;
    double d;
};

/* A union like class is either 
1) A standard union
2) A non-union class which has atleast one anonymous union (like below).

A union like class has variant members which are
a) the non static members of the anonymous union declared in the non-union class. So i, c, d are variant members.
b) the non static data members of a standard union which are not anonymous unions.
*/
struct S {
    enum {CHAR, INT, DOUBLE} tag;

    union {
        int i;
        char c;
        double d;
    };
};

void print(const S& s) {
    switch(s.tag) {
        case S::CHAR: cout << "char in S is: " << s.c << endl; break;
        case S::INT: cout << "int in S is: " << s.i << endl; break;
        case S::DOUBLE: cout << "double in S is: " << s.d << endl; break;
    }
}

int main() {
    union {
        int i;
        const char* p;
    };

    i = 10; // i and p are available in enclosing scope.
    cout << "i: " << i << endl;
    p = "HelloWorld";
    cout << "p: " << p << endl;

    S s;
    s.tag = S::CHAR;
    s.c = 'T';
    print(s);
    s.tag = S::INT;
    s.i = -100;
    print(s);
    return 0;
}


