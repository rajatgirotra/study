/*
 * Views on lvalues usually have reference semantics. this means that usually:
 *    If elements of the referred range are modified, the elements of the view were modified.
 *    If elements of the view are modified, the elements of the referred range were modified.
 *
 * borrowed_iterators: A lot of algorithms in std::ranges namespace take a range argument and return an iterator in that range as a result.
 * but what if the range argument is passed as a temporary (prvalue)?
 * the returned iterator MAY NOT be de-referenced - otherwise it MAY cause undefined behavior because the range object is already
 * destroyed after the algorithm is executed. However, this is not always the case as you explained below.
 *
 * borrowed_range: In the Ranges library, a borrowed range is defined as a range where it's safe to use its iterators even after the range object
 * (the "view") goes out of scope. This concept is useful for preventing dangling iterators in algorithms like std::ranges::find.
 * this can happen,
 * 1) if the iterators of the range are independent of the lifetime of the underlying range.
 * 2) or if the iterators themselves store the values which need to be iterated upon.
 *
 * many range algorithms return a borrowed_iterator type, it means it employs special compile time check to see if the passed argument is a borrowed_range<> or not.
 * If you look at how the borrowed_iterator_t<> is defined, it will become very clear.
 *
 * template<class R>
 * using borrowed_iterator_t = conditional_t<borrowed_range<R>, iterator_t<R>, dangling>;
 * i.e. borrowed_iterator_t is actually a compile time conditional and return rng::dangling for a non-borrowed range.
 * to get around this problem, a number of standard algo's return a borrowed_iterator type.
 *
 * iterator_t<R> is a type trait, which returns the iterator type for the range.
 *
 * Now if the argument to say, rng::find() is an lvalue, then borrowed_range<R> will return true for lvalue ranges always, so you will
 * get back a proper iterator.
 *
 * But for rvalues, what borrowed_range<R> will return depends on whether the underlying source range is a borrowed range or not.
 * i.e. mostly:
 * enable_borrowed_range<AdaptorView<R>> = enable_borrowed_range<R>
 * So you can say borrowed-ness propagates from the source.
 *
 * Examples of borrowed_ranges:
 *
 * 1) rng::iota_view --> in this view, the iterator itself stores the current value to be used and incremented.
 * 2) rng::empty_view --> in this view, the iterator always points to the end iterator so there are no elements to be traversed.
 * 3) views where the iterators directly refer to the underlying range on which the view is constructed. This is the case with
 *    3.a) std::string_view (is borrowed_range because it points to a buffer in an underlying string object)
 *    3.b) rng::ref_view (because it points to an underlying buffer)
 *    3.c) std::span
 *    3.d) std::ranges:subrange
 * Example:
 * auto it1 = std::ranges::find(std::string_view("hello"), 'e'); // OK: string_view is a borrowed range
 * auto it2 = std::ranges::find(std::string("hello"), 'e');      // BAD: string is not a borrowed range, it2 will be rng::dangling
 *
 * auto it = std::ranges::find(std::views::take(std::string_view("hello"), 3), 'e'); // this is also valid.
 *
 * std::string str = "hello";
 * auto v = std::views::take(str, 3); // again valid as range argument is lvalue and borrowed_range<R> will return true for lvalues.
 *
 * A borrowed iterator concept ensures that the iterator returned can outlive the range object, so it is safe to dereference.
 * If the iterator cannot be safely dereferenced, it results in a compile time error.
 *
 * This is the reason a borrowed_iterator type was called a safe iterator in the early version of the standard.
 */
#include <iostream>
#include <ranges>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>
#include <random>
#include <iterator>
#include <type_traits>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

auto getData() {
    std::vector v{1,2,3,4,5};
    return v;
}

int main() {

    auto pos = std::ranges::find(getData(), 2);
    static_assert(std::is_same_v<decltype(pos), std::ranges::dangling>);

    // cout << *pos << endl; // error. will not compile, saving you from runtime undefined behavior.

    // the way out is to use lvalue instead to capture the return value from getData(). this extends the lifetime of the temporary.
    auto&& data = getData();
    auto pos2 = std::ranges::find(data, 2);
    if(pos2 != data.end()) {
        cout << "Found: " << *pos2 << endl;
    }

    // Note that borrowed iterators can still dangle if the underlying range object goes out of scope and gets destroyed.
    // This will result in undefined behavior at runtime.
}

/*
 * process(std::ranges::find(getData(), 42)); // compile time error
 *
 * Note that in the above case, the range returned by getData() gets destroyed only after the process() function call,
 * still find returns std::ranges::dangling, because getData() returns std::vector<int> which is not a borrowed_range<>
 */
