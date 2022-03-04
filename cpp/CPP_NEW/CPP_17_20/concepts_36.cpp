/*
 * concepts in C++20 allow you to write generic code in a readable way. It produces better error messages when requirements/constraints are broken
 * better diagnostics and avoids writing a lot of boiler plate.
 *
 * Lets see
 */

#include <iostream>
using namespace std;

//simple template to compare and return max out of them. but let say we want to disable this template for pointer types.
// as for pointer types this code is comparing pointers not their values. So we can introduce a "requires clause"
template <typename T>
T maxValue(T a, T b) {
    return a < b ? b : a;
}

template <typename T>
requires (!std::is_pointer_v<T>) // the requires clause should be followed by a COMPILE TIME boolean expression. the compiler will now behave
// like there was no maxValueWithRequiresClause defined for pointers
// THIS COMPILE TIME BOOLEAN EXPRESSION IS CALLED A CONSTRAINT.
T maxValueWithRequiresClause(T a, T b) {
    return a < b ? b : a;
}

// when you want to re-use a constraint at multiple places, you create a concept out of it.
// So a concept is a named requirement, i.e. when you give a name to a requirement, it is a concept. example
template <typename T>
concept IsPointer = std::is_pointer_v<T>; // concept means you are just giving a name to a set of constraints.
// the value again should be a COMPILE TIME boolean expression. We can now use this constraint like.

template <typename NonPointerType>
requires (!IsPointer<NonPointerType>)
NonPointerType maxValueWithConcept(NonPointerType a, NonPointerType b) {
    return a < b ? b : a;
}

// overload maxWithWithConcept for Pointers
template <typename PointerType>
requires IsPointer<PointerType> // no parenthesis required when the clause is just the name of a concept
auto maxValueWithConcept(PointerType a, PointerType b) { // return type should be auto, not PointerType
    return maxValueWithConcept(*a, *b);
}

// ordinary template for minValue
template <typename T>
T minValue(T a, T b) {
    return (a < b ? a : b);
}

template <typename T>
requires IsPointer<T> // templates with constraints are assumed to be more specialized compared to those who don't have constraints.
auto minValue(T a, T b) {
    return minValue(*a, *b);
}

//Type constraints
/*
 * if you have a constraint which is concept involving only one template parameter, you can use a shorthand notation for using it
 * you can replace the "typename" keyword with the concept name
 */
template <IsPointer T>
auto minValueTypeConstraint(T a, T b) {
    return minValue(*a, *b);
}

auto maxValueAutoArguments(auto a, auto b) {
    return a > b ? a : b;
}

// you could also use the following syntax with "auto" function argument types.
auto maxValueAutoArgumentsConstraint(const IsPointer auto a, const IsPointer auto b) {
    return maxValueAutoArguments(*a, *b);
}
// but what if you want to add another requirement above: that the types a and b should be comparable. When you need to put a requirement on the argument types,
// you can use the trailing requirements clause, that way you can use decltype(*a) and dectype(*b)

auto maxValueAutoArgumentsConstraintWithTrailingRequires(const IsPointer auto a, const IsPointer auto b)
requires std::three_way_comparable<decltype(*a), decltype(*b)> {
    return maxValueAutoArguments(*a, *b);
}


int main() {
    int x = 10, y = 20;
    cout << "maxValueWithRequiresClause(x, y): " << maxValueWithRequiresClause(x, y) << endl;

    // error: no matching function for call to ‘maxValueWithRequiresClause(int*, int*)’
//    cout << "maxValueWithRequiresClause(&x, &y): " << maxValueWithRequiresClause(&x, &y) << endl;

    cout << "maxValueWithConcept(x, y): " << maxValueWithConcept(x, y) << endl;
    cout << "maxValueWithConcept(&x, &y): " << maxValueWithConcept(&x, &y) << endl;
    int* px = &x, *py = &y;
    cout << "maxValueWithConcept(&px, &py): " << maxValueWithConcept(&px, &py) << endl; // works recursively. as &px, &py are int**

    cout << "minValueTypeConstraint(&x, &y): " << minValueTypeConstraint(&x, &y) << endl;

    cout << "maxValueAutoArgumentsConstraint(&x, &y): " << maxValueAutoArgumentsConstraint(&x, &y) << endl;
    double d = 1.5;
//    double* pd = &d;
    cout << "maxValueAutoArgumentsConstraint(&x, &pd): " << maxValueAutoArgumentsConstraint(&x, &d) << endl; // when using auto, a and b can be different types.
}

