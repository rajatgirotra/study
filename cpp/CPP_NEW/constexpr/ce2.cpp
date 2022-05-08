#include <iostream>
#include <type_traits>
using namespace std;

void free_func() {
    /* Before C++11 (you would declare pi as static and that would have made the function not thread safe. With C++11/14,
     * static initialization is now protected, all modern compilers typically use locks. But with constexpr, the compiler
     * ensures that "pi" has a value before the function is called. So there is no need to use any locks.
     * So it is much more efficient. */
    constexpr double pi = 3.14159265;
//    static const double pi = 3.14159265;
    static_assert((pi > 3.1) && (pi < 3.2), "pi should be between 3.1 and 3.2");
    cout << pi * 10 << endl;
}

int main() {
    free_func();
    return 0;
}
    
/*
  I saw no difference when i saw the assembly in gcc.explorer by Matt Godbolt. between constexpr or static const
  Also you cannot have a static variable in a function declared constexpr.
  
  Looks like compiler optimizes out static const variable if the value is known at compiler time. so whether we use static const or constexpr, it doesnt seem to make a difference.
  */
