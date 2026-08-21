/*
 * trivial type - A type in which all special members are compiler generated (ctor, dtor, copy ctor etc).
 * even X()=default; make a type non trivial.
 *
 * standard layout - A type in which the memory layout is predictable and compatible with C. i.e. offset_of, reinterpret_cast
 * work well with it.
 *
 * POD type : A type which is trivial and has standard layout.
 *
 * Aggregate types: A type which can be constructed directly using brace initialization.
 * Again, having a hand written constructor at the top level class make a type non aggregate.
 */

#include <iostream>
#include <string>
#include <optional>
#include <type_traits>
using namespace std;

// trivial + standard + aggreggate
struct P { int x; int y;};

// NOT trivial, std::string has default constructor, not standard layout, as size of string can vary on platforms
// but is aggregate type (std::string has a ctor but that is fine, as long as A does not have a ctor.
struct A { int id; std::string name; };

// not trivial due to default constructor, but standard layout and aggregate type as well.
struct SL { SL() { x = 0; } int x; };   // also not an aggregate as SL has a ctor.

// Trivial type, and NOT standard type - mixed access control
// Also NOT aggregate as cannot use brace initialization due to 'b' being non public so cannot create object of T using
// brace initialization
struct T { public: int a; private: int b; };


// Also with C++17 you have structural types. Structural types are types which can be used a NON Type template parameters as template arguments.
/*
 * so if you have to create a structural type, what do you have to keep in mind.
 * 1. a structural type and all of its base classes must have only public members (not marked as mutable)
 * and they must all be literal class type or array of literal type.
 * literal type just means a type with constexpr constructor (either implicit or explicitly written) and constexpr/trivial destructor.
 * literal type just means compiler knows how to represent these values at compile time.
 */
// Example below of structural types:
/*
*
template <std::size_t N>
struct FixedString {
    char data[N]{};                    // public, non-mutable, array of structural type
    constexpr FixedString(const char (&s)[N]) {
    std::copy_n(s, N, data);       // constexpr since C++20
    }
};

Note that FixedString isn't an aggregate (it has a user-declared ctor), which is fine — structural doesn't require aggregate
*/
struct Coord
{
    int x; int y;
};

template <Coord C>
struct Grid
{
    Grid()
    {
        cout << "Grid::Grid(" << C.x << ", " << C.y << ")" << endl;
    }
};


int main()
{
    Grid<Coord{1, 2}> g;

    static_assert(std::is_trivially_default_constructible_v<P>
        && is_trivially_copyable_v<P>
        && std::is_standard_layout_v<P>);

    static_assert(std::is_aggregate_v<A>);

    static_assert(std::is_standard_layout_v<SL>
        && !std::is_trivially_default_constructible_v<SL>
        && is_trivially_copyable_v<SL>);

    static_assert(std::is_trivially_default_constructible_v<T>
        && is_trivially_copyable_v<T>
        && !std::is_standard_layout_v<T>);
}

