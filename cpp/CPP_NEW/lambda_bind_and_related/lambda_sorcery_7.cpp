
#include <iostream>
#include <functional>
#include <type_traits>
using namespace std;


int main() {
/* What sorcery is this? */
    (+[](){})();
}

/*
 * The unary plus operator can be applied to an arithmetic type, an unscoped enumeration or to a pointer type and the result is that type itself.
 * like +5 is 5
 * enum Color { ORANGE, RED}; Color c = ORANGE; +c will be ORANGE
 * and similarly for pointer types. The above works because a capture less lambda contains an implicit conversion operator to a function pointer.
 * So applying + to a capture less lambda returns a function pointer and that is immediately invoked. so it's just a way fancy of doing nothing.
 */
