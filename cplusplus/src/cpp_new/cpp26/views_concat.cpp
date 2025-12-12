/**
 * cpp26 add a new view adaptor in std::ranges::views, called "concat()". it can take multiple ranges and give you a combined
 * view of it. this new view you use to iterate over, filter, transform, take, drop, find etc.
 *
 * you have to be careful though when the concat() adaptor takes a range both by lvalue and rvalue and you try to get a pointer in it.
 *
 */

#include <ranges>
#include <print>
#include <vector>
#include <set>
#include <array>
#include <list>
#include <cxxabi.h>

using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

namespace {
    auto demangle(const char* mangled_name) {
        int res {-1};
        auto s = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &res);
        string sres (mangled_name);
        if (res == 0) {
            sres = s;
            free(s);
        }
        return sres;
    }
}

template <typename T>
void print_type_and_value(T&& t) {
    std::println("type: {}, value: {}", demangle(typeid(T).name()), std::forward<T>(t));
}


void update(std::vector<int>& v1, std::vector<int>& v2) {
    vws::concat(v1, v2)[7] = 100; // possible. because both v1 and v2 are random access, so the combined view will support random access operator.
}

void update([[maybe_unused]] std::vector<int>& v1, [[maybe_unused]] std::list<int>& l1) {
    // vws::concat(v1, l1)[3] = 100; // doesn't compile. as std::list<> doesnt support random access.
}

auto getData() {
    return std::vector {101, 102, 103, 104};
}


int main() {
    std::array a1{1, 2, 3, 4};
    std::vector v1{5, 6, 7, 8};
    std::list l1{9, 10, 11, 12};
    std::set s1{13, 14, 15, 16};

    for (auto& val : vws::concat(s1, l1, v1, a1)) {
        std::println("{}", val);
    }

    update(v1, v1);
    std::println("After update");
    for (auto& val : vws::concat(v1)) {
        std::println("{}", val);
    }

    auto pos = [&]() {
        auto c_view = vws::concat(v1, l1);
        return rng::find(c_view, 9); // find 9, argument c_view to find() is lvalue, so returned borrowed_iterator_t is safe and not dangling.
    }();
    // c_view is gone by now.
    std::println("pos: {}", *pos);

    auto pos2 = [&]() {
        auto c_view = vws::concat(v1, getData()); // concat called with both lvalue and rvalue view and we try to find something in getData(). a recipe for disaster.
        return rng::find(c_view, 101); // find 101, argument c_view to find() is lvalue, so returned borrowed_iterator_t is safe and not dangling.
        // however, the iterator returned will be inside the temporary list getData() so dereferencing pos2 will be undefined behavior.
    }();
    // c_view is gone by now.
    std::println("pos2: {}", *pos2); // print gibberish, undefined behavior

    auto pos3 = [&]() {
        return rng::find(vws::concat(v1, v1), 4); // find 101, argument c_view to find() is rvalue, so returned borrowed_iterator_t is dangling.
    }();
    // std::println("pos3: {}", *pos3); // cannot dereference, it is ranges::dangling rightly
}