/*
 * Concepts was introduced to simplify the use of SFINAE.
 * Basically concepts allow you to constraint arguments to functions, the return type from functions or even variables.
 */

#include <type_traits>
#include <iostream>
using namespace std;

// Let say you require a function with two arguments and both should be float.
//template <typename T, typename std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
//auto value (T val1, T val2) {
//    cout << "No concept overload\n";
//    return val1 + val2;
//}
//int main() {
//    cout << value(1.0, 2.5) << endl;
//}

// the same function can be re-written in C++20 using concepts
//template <typename T>
//auto value (T val1, T val2) requires std::is_floating_point_v<T>
//{
//    cout << "concept overload - first way\n";
//    return val1 + val2;
//}
//int main() {
//    cout << value(1.0, 2.5) << endl;
//}

// another way of writing concepts
//template <typename T>
//concept f_point = std::is_floating_point_v<T>;
//
//template <f_point T>
//auto value(T val1, T val2) {
//    cout << "concept overload - second way\n";
//    return val1 + val2;
//}
//int main() {
//    cout << value(1.0, 2.5) << endl;
//}


// third way of writing concepts
//template <typename T>
//concept f_point = std::is_floating_point_v<T>;
//
//auto value(f_point auto val1, f_point auto val2) {
//    return val1 + val2;
//}
///* Note the subtle difference, in the second way, both types MUST BE DOUBLE, but with this both must be floating point.
// * so float and double should also be ok
// */
//int main() {
//    cout << value(1.0, 2.5) << endl;
//}


// fourth way - putting concept to return type
//template <typename T>
//concept f_point = std::is_floating_point_v<T>;
//
//f_point auto value(f_point auto val1, f_point auto val2) {
//    return val1 + val2;
//}
//
//int main() {
//    auto x = value(1.0, 2.5f);
//}


// one more way - putting concept to variable
//template <typename T>
//concept f_point = std::is_floating_point_v<T>;
//
//auto value(f_point auto val1, f_point auto val2) {
//    return val1 + val2;
//}
//
//int main() {
//    f_point auto x = value(1.0, 2.5f);
//}
