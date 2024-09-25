/*
 * Probably a big change introduced in C++17/C++20 is that when you iterate over a sequence using begin() and end() iterators, the type of
 * begin and end iterators need not be the same. Hmm.. why? and what purpose does it serve?
 *
 * Benefits
 * 1) Think that you want to perform some operation on the characters of a string literal or a char* string. You will first need to iterate over the string
 * just to find its end. So you have already iterated over the string once just to get the end iterator. NOT GOOD RIGHT!
 *
 * 2) Sometimes iterating over the sequence is not even an option. like for input stream iterators. as iterating over these sequences again will
 * yield different results.
 *
 * That is why C++17/C++20 introduced something called as sentinel. this sentinel is used to denote the end of a sequence.
 * So till now you understand a range object as having a begin and end iterator to represent a sequence. Well, there is more to it.
 *
 * Let's see it in action
 */
#include <iostream>
#include <string>
#include <concepts>
#include <ranges>
#include <algorithm>
#include <vector>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

struct NullTerm {
    bool operator == (auto pos) const noexcept {
        return *pos == '\0';
    }
};

template <auto End>
struct EndSentinel {
    bool operator == (auto pos) const noexcept {
        return *pos == End;
    }
};

template <typename CharT>
constexpr auto my_strlen(const CharT* const s) {
    // std::unreachable_sentinel is special. It just means there is no end to range. So comparing whether we have reached the end
    // at every iteration is pointless. you can say it is sort of optimization.
    return std::ranges::find(s, std::unreachable_sentinel, CharT{}) - s;
}

int main() {
    const char* rawString {"RajatGirotra"};

    /* if you have read the spaceship operator code in this folder. you should know that
     * pos != NullTerm{}, results in compiler searching for !(pos == NullTerm{}) and then !(NullTerm{} == pos); and the latter is available
     */
    for(auto pos = rawString; pos != NullTerm{}; ++pos) {
        cout << *pos << " ";
    }
    cout << endl;


    rng::for_each(rawString, NullTerm{}, [](auto ch) {
        cout << "ch: " << ch << endl;
    });
    // If you look at how rng::for_each is defined, one of its overloads takes an iterator as first argument, and a sentinel as a second argument.

    // range-based for loops also support iterator/sentinel
    std::ranges::subrange rawStringRange (rawString, NullTerm{}); // Don't worry too much about subrange, we discuss it in the next code file.
    for(char c : rawStringRange) {
        cout << ' ' << c;
    }
    cout << endl;

    std::vector intVec {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // create a sentinel to stop after we reach value == 7.
    std::ranges::subrange intRange(intVec.begin(), EndSentinel<7>{});
    for(auto&& i : intRange) {
        cout << i << " ";
    }
    cout << endl;

    std::ranges::sort(intRange);
    std::ranges::for_each(intRange, [](int v) {
        cout << v << " - ";
    });
    cout << endl;

    static_assert(my_strlen("RajatGirotra") == 12);

};