
/* find out at compile time if a function has a serialize() member function or not.
 * Then also write a generic serialize function which will call obj.serialize() if object has serialize method
 * otherwise call to_string(obj) to serialize it.
 *
 * This is the first attempt, We'll do three attempts. Read serialize.hpp first
 */
#include "serialize.hpp"
#include <type_traits>
using namespace std;

template <typename T>
struct hasSerialize {
private:
    // typical way of using sfinae.
    using no = char;
    struct yes { no _[2]; };

    template <typename C, C u> struct reallyHas;

    template <typename U>
    static constexpr no test(...); // the black hole which will match everything

    template <typename U>
    static constexpr  yes test(reallyHas<std::string (U::*)(), &U::serialize>*);
    template <typename U>
    static constexpr  yes test(reallyHas<std::string (U::*)() const, &U::serialize>*);

public:
    static constexpr bool value = (sizeof(test<T>(0)) == sizeof(yes)) ;
};

template <typename T, typename std::enable_if<hasSerialize<T>::value>::type* = nullptr>
std::string serialize(const T& t) {
    return t.serialize();
}

template <typename T, typename std::enable_if<!hasSerialize<T>::value>::type* = nullptr>
std::string serialize(const T& t) {
    return to_string(t);
}
