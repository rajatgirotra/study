#include "p.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <bitset>
#include <utility>
#include <iterator>
#include <algorithm>
#include <typeinfo>
using namespace std;

//template <typename T>
//T max_(T&& a, T&& b) {
//    return (a > b) ? a : b;
//}
//
//class Integer {
//    int m_val = 0;
//public:
//    Integer(int arg) : m_val(arg) {}
//
//    bool operator > (const Integer& rhs) {
//        return m_val > rhs.m_val;
//    }
//    friend ostream& operator << (ostream& os, const Integer& rhs) {
//        return os << rhs.m_val;
//    }
//};
//int main() {
//    Integer i1(10), i2 (20);
//    double d1 = 5.6, d2 = 5.8;
//    cout << "max_(i1, i2): " << boolalpha << max_(i1, i2) << endl;
//    cout << "max_(d1, d2): " << boolalpha << max_(d1, d2) << endl;
//}
// ------------------------------------------------------------------------------------------
//static constexpr unsigned int SIZE = 20;
//template <typename T, unsigned int N = SIZE>
//class Stack {
//    T m_data[N];
//    unsigned int index = 0;
//public:
//    void push(T arg);
//    T pop();
//};
//
//template <typename T, unsigned int N>
//void Stack<T, N>::push(T arg) {
//    if (index >= N)
//        throw std::runtime_error("stack full. push failed!");
//    m_data[index++] = arg;
//}
//template <typename T, unsigned int N>
//T Stack<T, N>:: pop() {
//    if (index <= 0)
//        throw std::runtime_error("stack empty. pop failed!");
//    return m_data[--index];
//}
//
//
//template <typename T, template <typename, unsigned int = 20> class Seq>
//class Container {
//    Seq<T, 20> m_seq;
//public:
//    void push(T arg);
//    T pop();
//};
//
//template <typename T, template<typename, unsigned int> class Seq>
//void Container<T, Seq>::push(T arg) {
//    m_seq.push(arg);
//}
//
//template <typename T, template<typename, unsigned int> class Seq>
//T Container<T, Seq>::pop() {
//    return m_seq.pop();
//}
//
//int main() {
//    Container<int, Stack> container;
//    try {
//        for (int i = 0; i < 21; ++i) {
//            container.push(i * 5);
//        }
//    } catch (const std::exception &e) {
//        cerr << "caught exception: " << e.what();
//    }
//
//    try {
//        for (int i = 0; i < 21; ++i) {
//            cout << container.pop() << "\n";
//        }
//    } catch (const std::exception &e) {
//        cerr << "caught exception: " << e.what();
//    }
//}
// ------------------------------------------------------------------------------------------

//template <typename T, template <typename U, typename = std::allocator<U>> class Seq>
//class Container {
//    Seq<T> m_seq;
//public:
//    void push_back(const T& arg);
//
//    typename Seq<T>::const_iterator cbegin();
//    typename Seq<T>::const_iterator cend();
//};
//
//template <typename T, template<typename, typename>class Seq>
//void Container<T, Seq>::push_back(const T& arg)
//{
//    m_seq.push_back(arg);
//}
//
//template <typename T, template<typename U, typename = std::allocator<U>>class Seq>
//typename Seq<T>::const_iterator Container<T, Seq>::cbegin() {
//    return m_seq.cbegin();
//}
//
//template <typename T, template<typename U, typename = std::allocator<U>>class Seq>
//typename Seq<T>::const_iterator Container<T, Seq>::cend() {
//    return m_seq.cend();
//}
//
//int main() {
//    Container<int, list> list_container;
//    for(int i = 0; i < 5; ++i)
//        list_container.push_back(i);
//
//    for(auto iter = list_container.cbegin(); iter != list_container.cend(); ++iter)
//        cout << *iter << endl;
//
//    Container<string, vector> vector_container;
//    for(int i = 0; i < 5; ++i)
//        vector_container.push_back(string("Rajat ").append(to_string(i)));
//
//    for(auto iter = vector_container.cbegin(); iter != vector_container.cend(); ++iter)
//        cout << *iter << endl;
//}

// ------------------------------------------------------------------------------------------

//template <typename Seq>
//void print_sequence(const Seq& seq) {
//    for (const auto& item : seq) {
//        cout << item << endl;
//    }
//}
//
//int main() {
//    std::vector<string> s{"A", "B", "C", "D"};
//    print_sequence(s);
//}
// ------------------------------------------------------------------------------------------
//
//template <typename T>
//T sum(T* b, T* e, T init = T()) {
//    auto sum = init;
//    while (b!=e) {
//        sum += *b;
//        ++b;
//    }
//    return sum;
//}
//
//int main() {
//    int arr[] {1,2,3,4,5,6};
//    cout << sum(arr, arr+sizeof(arr)/sizeof(arr[0]));
//}
// ------------------------------------------------------------------------------------------

//template <typename CharT, size_t N>
//typename std::basic_string<CharT> bitsetToString(const bitset<N>& bs) {
//    return bs.template to_string<CharT>();
//}
//
//int main() {
//    bitset<10> bs {7};
//    cout << bs.to_string() << endl;
//    cout << bitsetToString<char>(bs) << endl;
//}
//
// ------------------------------------------------------------------------------------------

//template <typename T>
//class Box;
//
//template <typename T>
//Box<T> operator + (const Box<T>& lhs, const Box<T>& rhs);
//
//template <typename T>
//ostream& operator << (ostream& os, const Box<T>& rhs);
//
//template <typename T>
//class Box {
//    T m_val;
//public:
//    Box(T arg=T()) : m_val(arg) {}
//
//    friend Box<T> operator+ <>(const Box<T>& lhs, const Box<T>& rhs);
//    friend ostream& operator<< <>(ostream& os, const Box<T>& rhs);
//};
//
//template <typename T>
//Box<T> operator+ (const Box<T>& lhs, const Box<T>& rhs) {
//    return Box<T>(lhs.m_val + rhs.m_val);
//}
//
//template <typename T>
//ostream& operator<< (ostream& os, const Box<T>& rhs) {
//    return os << "[" << rhs.m_val << "]\n";
//}
//
//int main() {
//    Box<int> b1(10), b2(-5);
//    cout << b1 + b2;
//}
// ------------------------------------------------------------------------------------------
//auto sum_diff(int a, int b) {
//    return std::make_pair(a+b, a-b);
//}
//
//int main() {
//    auto [x, y] = sum_diff(10, 10);
//    cout << "sum: " << x << endl;
//    cout << "diff: " << y << endl;
//}
// ------------------------------------------------------------------------------------------

//template <typename T>
//struct has_iterator {
//private:
//    using yes = char;
//    struct no { yes _[2]; };
//
//    template <typename U>
//    static no has(...);
//    template <typename U>
//    static yes has(typename U::iterator*);
//
//public:
//    static constexpr bool value = (sizeof(has<T>(0))== sizeof(yes));
//};
//

//template <typename T, typename = bool>
//struct has_iterator : false_type {};
//
//template <typename T>
//struct has_iterator<T, decltype(declval<T::iterator>(), bool())> : true_type {};
//
//struct X {
//    struct iterator {};
//};
//
//int main() {
//    cout << std::boolalpha << "has_iterator<X>: " << has_iterator<X>::value << endl;
//    cout << std::boolalpha << "has_iterator<int>: " << has_iterator<int>::value << endl;
//}
// ------------------------------------------------------------------------------------------

//struct TypeHolder {
//    enum struct my_type_t { int_type, float_type};
//    my_type_t m_type;
//
//    template <typename Integer, typename std::enable_if_t<std::is_integral_v<Integer>>* = nullptr>
//    TypeHolder(Integer) : m_type(my_type_t::int_type) {}
//
//    template <typename Real, typename std::enable_if_t<std::is_floating_point_v<Real>>* = nullptr>
//    TypeHolder(Real) : m_type(my_type_t::float_type) {}
//
//};
//
//template <typename T, typename... Args>
//bool construct(T, Args...) {
//    return false;
//}
//
//template <typename T, typename... Args>
//double construct(T, Args... ) {
//    return 5.5;
//}
//
//int main() {
//
//    construct(0);
//    TypeHolder th1(10);
//    TypeHolder th2(0.);
//}
// ------------------------------------------------------------------------------------------
//
//template <typename T, typename std::enable_if_t<std::is_integral_v<T>>* = nullptr>
//void foo(T) {
//    cout << "T is integer type\n";
//}
//
//template <typename T, typename std::enable_if_t<std::is_class_v<T>>* = nullptr>
//void foo(T) {
//    cout << "T is class type\n";
//}
//
//class X {};
//
//int main() {
//    foo(100);
//    foo(X());
//}
// ------------------------------------------------------------------------------------------

//template <typename T, typename... Args>
//typename std::enable_if<std::is_integral_v<T>, bool>::type
//foo(T, Args&&...) {
//    cout << "foo returns bool\n";
//    return true;
//}
//
//template <typename T, typename... Args>
//typename std::enable_if<std::is_floating_point_v<T>, double>::type
//foo(T arg, Args&&...) {
//    cout << "foo returns double\n";
//    return arg;
//}
//
//int main() {
//    foo(100);
//    foo(4.4);
//}
// ------------------------------------------------------------------------------------------

//struct A {
//    std::string serialize() const {
//        return "I am A";
//    }
//};
//
//struct B {};
//std::string to_string(const B&) {
//    return "I am B";
//}
//
//struct C {
//    std::string serialize() const {
//        return "I am C";
//    }
//};

//template <typename T>
//struct has_serialize {
//private:
//    using yes = char;
//    struct no { true_type _[2]; };
//
//    template <typename U, U u> struct reallyHas;
//
//    template <typename C>
//    static no& has(...);
//    template <typename C>
//    static yes& has(reallyHas<std::string (C::*)(), &C::serialize>*);
//    template <typename C>
//    static yes& has(reallyHas<std::string (C::*)() const, &C::serialize>*);
//public:
//    static constexpr auto value = (sizeof(has<T>(0)) == sizeof(yes));
//};

//template <typename T>
//struct has_serialize {
//private:
//    using yes = char;
//    struct no { true_type _[2]; };
//
//    template <typename C> static constexpr bool test(...) { return false; }
//    template <typename C> static constexpr decltype(declval<C>().serialize(), bool()) test(int) { return true; }
//public:
//    static constexpr auto value = test<T>(0);
//};

//template <typename T, typename = std::string>
//struct has_serialize : std::false_type {};
//
//template <typename T>
//struct has_serialize<T, decltype(declval<T>().serialize())> : true_type {};

//template <typename T>
//std::string serialize(T&& arg) {
//    if constexpr (has_serialize<T>::value) {
//        return std::forward<T>(arg).serialize();
//    }
//    if constexpr (!has_serialize<T>::value){
//        return std::to_string(std::forward<T>(arg));
//    }
//}
//
//template <typename T>
//typename std::enable_if_t<has_serialize<T>::value, std::string> serialize(const T& arg) {
//    return arg.serialize();
//}
//
//template <typename T>
//typename std::enable_if_t<!has_serialize<T>::value, std::string> serialize(T&& arg) {
//    return to_string(std::forward<T>(arg));
//}
//
//int main() {
//    cout << "has_serialize<A>: " << boolalpha << has_serialize<A>::value << endl;
//    cout << "has_serialize<B>: " << boolalpha << has_serialize<B>::value << endl;
//    cout << "has_serialize<C>: " << boolalpha << has_serialize<C>::value << endl;
//
//    cout << "serialize<A>: " << boolalpha << serialize(A()) << endl;
//    cout << "serialize<B>: " << boolalpha << serialize(B()) << endl;
//    cout << "serialize<C>: " << boolalpha << serialize(C()) << endl;
//}
// ------------------------------------------------------------------------------------------

//template <long FROM, long TO>
//struct Range {
//private:
//    struct iterator {
//        using iterator_category = forward_iterator_tag;
//        using value_type = long;
//        using difference_type = long;
//        using pointer = long*;
//        using reference = long;
//    private:
//        value_type m_atValue;
//    public:
//        explicit constexpr iterator(value_type arg) noexcept : m_atValue(arg) {}
//
//        reference operator *() const {
//            return m_atValue;
//        }
//
//        iterator& operator ++() {
//            ++m_atValue;
//            return *this;
//        }
//
//        iterator& operator ++(int) {
//            iterator ret(*this);
//            ++m_atValue;
//            return ret;
//        }
//
//        bool operator == (const iterator& rhs) {
//            return m_atValue == rhs.m_atValue;
//        }
//
//        bool operator != (const iterator& rhs) {
//            return !(*this == rhs);
//        }
//    };
//
//public:
//    iterator begin() {
//        return iterator(FROM <= TO ? FROM : TO);
//    }
//
//    iterator end() {
//        return iterator(TO >= FROM ? TO+1 : FROM+1);
//    }
//};
//
//int main() {
//    auto r = Range<10, 20>();
//    std::copy(r.begin(), r.end(), ostream_iterator<long>(cout, " "));
//
//    cout << endl;
//    auto r2 = Range<20, 10>();
//    std::copy(r2.begin(), r2.end(), ostream_iterator<long>(cout, " "));
//
//    cout << endl;
//    for(auto&& item : r2) {
//        cout << item << " ";
//    }
//}
// ------------------------------------------------------------------------------------------

template <typename Iter>
void algo(Iter, Iter, std::random_access_iterator_tag) {
    cout << "running algo for vectors;\n";
}

template <typename Iter>
void algo(Iter , Iter , std::forward_iterator_tag) {
    cout << "running algo for lists;\n";
}

template <typename Iter>
void algo(Iter begin, Iter end) {
    algo(begin, end, typename std::iterator_traits<Iter>::iterator_category());
}

int main() {
    vector<int> v;
    list<int> l;

    algo(v.begin(), v.end());
    algo(l.begin(), l.end());
}