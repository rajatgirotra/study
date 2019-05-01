// std::enable_if. Very trivial. Defined in gcc as
/*
 * template <bool B, typename T = void>
 * struct enable_if{};
 *
 * template<typename T>
 * struct enable_if<true, T> {
 *     typedef T type;
 *  };
 *
 *  ie. partial specialization for true declares a typedef. and the "false" one doesn't have a typedef.
 *
 *  How is it used. Many ways
 *  1) To conditionally remove functions from overload resolution based on type_traits.
 *  2) to provide separate function overloads and specializations based on type_traits
 *  3) as arguments to function
 *  4) as function return types
 *  5) as templates parameters for class templates or function templates.
 */
#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

/* Why is the following illegal. Using std::enable_if as function template parameter
 *
 */
struct TypeHolder {
    enum struct type_t { int_type, float_type } m_type;

    // First c'tor for integers
//    template <typename Integer, typename = std::enable_if_t<std::is_integral<Integer>::value>>
  //  TypeHolder(Integer value) : m_type(type_t::int_type) {};

    // second c'tor for floats
    // template <typename Floating, typename = std::enable_if_t<std::is_floating_point<Floating>::value>>
    // TypeHolder(Floating value) : m_type(type_t::float_type) {};


    template <typename Integer, typename std::enable_if_t<std::is_integral_v<Integer>>* = nullptr>
    TypeHolder(Integer value) : m_type(type_t::int_type) {};

    template <typename Floating, typename std::enable_if_t<std::is_floating_point_v<Floating>>* = nullptr>
    TypeHolder(Floating value) : m_type(type_t::float_type) {};


};
// The reason is that "default template arguments ARE NOT PART OF FUNCTION TEMPLATE SIGNATURE. So the two function
// templates signatures are same, so you cannot overload them.
/*
 * template <typename Integer, typename> and template <typename Floating, typename>
 */


// Now lets see examples of 4 cases above
// 1st - using enable_if in function return types
template <typename T, typename... Args>
bool construct(T* t, Args&&... args) {
};

template <typename T, typename... Args>
double construct(T* t, Args&&... args) {
};
// The above two are just template functions, they are not really instantiated at the moment, so no problem
// in declaring them. If later I call construct(int*, 10), then the compiler will be confused which one to instantiate
// and will lead to ambiguous overload.

int main(int argc, char* argv[]) {
    int *poT = 0;
    // construct(poT, 10);

    TypeHolder objInt(10);
    TypeHolder objFloat(3.4);
}