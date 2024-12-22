/*
 * create a function to add a value to a collection.
 * create a collection of ints. provide a separate overload for floating points but for now keep the implementation same.
 */

#include <concepts>
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <vector>
using namespace std;

template <typename Coll, typename T>
void add(Coll& coll, const T& value) {
    cout << "generic add\n";
    coll.push_back(value); // generic for all types.
}

template <typename Coll, std::floating_point T> // std::floating_point concept is defined in <concepts>
void add(Coll& coll, const T& value) {
    cout << "floating point add\n";
    coll.push_back(value); // for floating point
}

/*
 * If we try to add a floating point to an integer vector, the concept version of add() function will be called.
 * If -Wall and -Werror is enabled, it will give an error as you are doing a narrowing cast.
 * but if not enabled, you will get a warning which may escape. So you can add a concept to check for narrowing.
 */

// need to understand more how it works. Looks like std::same_as<TO[1]> expands to std::same_as<TO[0], TO[1]>
template <typename FROM, typename TO>
concept ConvertsWithNarrowing = std::convertible_to<FROM, TO> && // note the use of &&. ConvertsWithNarrowing requires std::convertible_to<> to be satified.
                                requires (FROM&& x) {
                                    {std::type_identity_t<TO[]>{std::forward<FROM>(x)}} -> std::same_as<TO[1]>;
                                };

template <typename Coll, typename T> // std::floating_point concept is defined in <concepts>
requires ConvertsWithNarrowing<T, typename Coll::value_type>
void addVersion2(Coll& coll, const T& value) {
    cout << "generic add\n";
    coll.push_back(value);
}


int main() {
   vector<int> intVec;
   add(intVec, 25.5);

    addVersion2(intVec, 5);
//    addVersion2(intVec, 5.6);
}

