/*
C++11 defines user defined literals. Very trivial you just have to overload the "" operator called the literal operator. Example:
std::chrono overloads the "h" literal likes this:

constexpr std::chrono::hours operator ""h(uint64_t hrs) {
    return std::chrono::hours(hrs);
}

auto day = 24h; // means day is std::chrono::hours representing 24 hours. So whatever argument is expected in the operator "" function, should be the prefix of the literal. Here 24 which is an int.

We call this a duration literal. Ie. the name depends on whatever the argument type is

NOTE THAT ALL LITERALS INTRODUCED BY THE DEVELOPER MUST BEGIN WITH UNDERSCORE FOLLOWED BY LOWERCASE.
LITERALS WITH UNDERSCORE FOLLOWED BY UPPERCASE ARE RESERVED, BUT ALLOWED, SO BETTER NOT USE THEM.

Let's see some examples.
*/

#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

/* for integer literals, like 12_w, 0xABC_p, the rules are
1) if literal opertaors _w(unsigned long long), _p(unsigned long long) exist, they will be called.
2) Otherwise a raw literal operator or a literal operator template (one and not both must be defined).
A raw literal operator is one which takes a "const char*", so that will be used, so 12 and 0xABC will be converted to const char*. If a raw literal is also absent, a literal operator template will be searched whose template arguments are the individual characters of the integer literal.
*/

#if 0
std::string operator "" _w(unsigned long long param) {
    cout << "operator "" _w(unsigned long long) called, param: " << param << endl;
    return std::to_string(param);
}
#endif

#if 0
std::string operator "" _w(const char* param) {
    cout << "operator "" _w(const char*) called" << "  param: " << param << endl;
    return "raw literal operator";
}
#endif 

#if 1
template <char... Args>
std::string operator "" _w() {
    cout << "literal operator template called, paramCount: " << sizeof...(Args) << endl;
    return "xyz";
}

template<>
std::string operator "" _w<'1', '2'>() {
    cout << "literal operator template specialization called, paramCount: 2" <<  endl;
    return "12";
}

#endif 


int main() {
    auto x1 = 12_w;
    //auto x1 = 0xABC_w;
    cout << x1 << endl;
    return 0;
}


/* Similar rules exist for floating point literals.
For string literals, 
ReturnType operator "" _X(const char*, size_t) 
is called where size_t is the length of the string literal w/o the terminating null character.

For character literals
ReturnType operator "" _X(const char*) 
is called
*/
