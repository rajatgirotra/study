/*
 * Define TypeList<Ts...> and write helpers Head<List>, Tail<List>, Length<List> using partial specialisation.
 */

#include <iostream>
#include <type_traits>
using namespace std;

namespace my
{
    template <typename... Types> struct list{};

    template <class List> struct head;
    template <typename First, typename... Rest> struct head<list<First, Rest...>>
    {
        using type = First;
    };

    template <class List> struct tail;
    template <typename Last> struct tail<list<Last>>
    {
        using type = Last;
    };

    template <typename First, typename... Rest> struct tail<list<First, Rest...>> : tail<list<Rest...>>
    {
    };

    template <typename List> struct length;
    template <typename... Types> struct length<list<Types...>>
    {
        static constexpr size_t value = sizeof...(Types);
    };
}