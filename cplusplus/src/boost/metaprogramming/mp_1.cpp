/*
 * We will understand some boost::mp11 constructs also implement a few ourselves so we learn metaprogramming.
 */
#include <filesystem>
#include <iostream>
#include <string>
#include <type_traits>
#include <functional>
#include <boost/mp11/mpl_list.hpp>

namespace mp11 = boost::mp11;
using namespace std;

namespace detail {
    template <bool Cond, typename T, typename E>  struct my_mp_if_impl { using type = T; };
    template <typename T, typename E>  struct my_mp_if_impl<false, T, E> { using type = E; };

    template <typename... Types, typename Callable>
    void my_mp_for_each_impl(mp11::mp_list<Types...>, Callable&& f) {
        using expand = int[];
        (void)expand {0, ((void)std::forward<Callable>(f)(Types{}), 0)...};
    }

    /*
     * ListType is actually a template class itself. This is a very common pattern to find the template parameters (T...)
     * of a template class which is passed as a template argument itself.
     */
    template <typename ListType> struct MySizeOfImpl {};
    template <template <typename...> class ListType, typename... Types> struct MySizeOfImpl<ListType<Types...>> {
        using type = std::integral_constant<std::size_t, sizeof...(Types)>;
    };
}

template <typename C, typename T, typename E>
using my_mp_if = detail::my_mp_if_impl<static_cast<bool>(C::value), T, E>::type;

template <bool C, typename T, typename E> struct my_conditional { using type = T; };
template <typename T, typename E> struct my_conditional<false, T, E> { using type = E; };
template <bool C, typename T, typename E> using  my_conditional_t = std::conditional_t<C, T, E>::type;

template <typename L, typename Callable>
void my_mp_for_each(Callable&& f) {
    detail::my_mp_for_each_impl(L{}, std::forward<Callable>(f));
}

struct A {
    A() { cout << "A::A" << endl; }
    ~A() { cout << "A::~A" << endl; }
};

struct B{};
struct C{};

template <typename T>
void foo() {
    cout << __PRETTY_FUNCTION__ << endl;
}

template <typename... Ts> struct MyTemplate {};

template <typename ListType>
struct MySizeOf {
    using type = detail::MySizeOfImpl<mp11::mp_rename<ListType, mp11::mp_list>>::type;
};

int main() {
    // mp_list is just a list of types.
    using types = mp11::mp_list<int, double, std::string, A>;
    [[maybe_unused]] types type_list;

    /*
     * let say you want to iterate over these types. you can use mp11:mp_for_each.
     * basically for your types A, B, C, mp11::mp_for_each<> will call your closure
     * with a dummy object of type A, B, C
     */
    mp11::mp_for_each<types>([]<typename T>([[maybe_unused]] const T& t) {
        foo<T>();
    });

    my_mp_for_each<types>([]<typename T>([[maybe_unused]] const T& t) {
        foo<T>();
    });

    // mp_if<Condition, T, E> is very similar to std::conditional_t
    static_assert(std::is_same_v<mp11::mp_if<mp11::mp_true, A, B>, A>);
    static_assert(std::is_same_v<my_mp_if<false_type, A, B>, B>);

    // mp_identity<T>::type is T
    static_assert(std::is_same_v<mp11::mp_identity<A>::type, A>);

    // mp_rename. Basically it takes variadic template parameters and forwards those template parameters
    // to another class which accepts variadic template. Example
    using L = mp11::mp_list<int, double, std::string>;
    using renamed_t = mp11::mp_rename<L, MyTemplate>;
    static_assert(std::is_same_v<renamed_t, MyTemplate<int, double, std::string>>);

    //mp_take and mp_drop are operate on mp_list<> and return another mp_list<> by taking/dropping a few types
    static_assert(std::is_same_v<mp11::mp_list<int, double>, mp11::mp_take<L, mp11::mp_size_t<2>>>);
    static_assert(std::is_same_v<mp11::mp_list<double, string>, mp11::mp_drop<L, mp11::mp_size_t<1>>>);

    //mp_bool<> is same as std::integral_constant
    static_assert(std::is_same_v<std::true_type, mp11::mp_bool<true>>);
    static_assert(std::is_same_v<std::false_type, mp11::mp_bool<false>>);
    static_assert(std::is_same_v<std::true_type, mp11::mp_not<mp11::mp_bool<false>>>);

    //mp_size<>, mp_at<>, mp_front<>, mp_back<>
    static_assert(std::is_same_v<mp11::mp_size<L>, mp11::mp_size_t<3>>);

    // you are passed a variadic type as a template parameter like MyType<T...>.
    // you need to return a ::type which is an integral constant with the count of sizeof...(T)
    // should be easy
    static_assert(std::is_same_v<MySizeOf<L>::type, std::integral_constant<std::size_t, 3>>);

}