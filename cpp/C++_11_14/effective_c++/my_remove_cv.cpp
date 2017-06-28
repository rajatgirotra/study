#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
struct remove_c { typedef T type; };

template<typename T>
struct remove_c<const T> { typedef T type; };

template <typename T>
struct remove_v { typedef T type; };

template<typename T>
struct remove_v<volatile T> { typedef T type; };

template <typename T>
struct my_remove_cv {
    typedef typename remove_v<typename remove_c<T>::type>::type type;
};

int main() {
    typedef remove_c<const int>::type type1;
    typedef remove_v<volatile int>::type type2;
    typedef my_remove_cv<const volatile int>::type type3;
    typedef my_remove_cv<const volatile int*>::type type4;
    typedef my_remove_cv<int* const volatile>::type type5;

    cout << "test1 " << (std::is_same<type1, int>::value ? "passed": "failed") << endl;
    cout << "test2 " << (std::is_same<type2, int>::value ? "passed": "failed") << endl;
    cout << "test3 " << (std::is_same<type3, int>::value ? "passed": "failed") << endl;
    cout << "test4 " << (std::is_same<type4, const volatile int*>::value ? "passed": "failed") << endl;
    cout << "test5 " << (std::is_same<type5, int*>::value ? "passed": "failed") << endl;
    cout << "test6 " << (std::is_same<std::remove_cv_t<int* const volatile>, int*>::value ? "passed": "failed") << endl;
    return 0;
}

