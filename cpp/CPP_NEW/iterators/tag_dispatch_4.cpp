#include <iostream>
#include <iterator>
#include <vector>
#include <list>
using namespace std;

namespace {
    template <typename BDIter>
    void alg(BDIter begin, BDIter end, std::bidirectional_iterator_tag) {
        cout << "alg implementation for bi-directional iterator\n";
    }

    template <typename RAIter>
    void alg(RAIter begin, RAIter end, std::random_access_iterator_tag) {
        cout << "alg implementation for random access iterator\n";
    }

    template <typename Iter>
    void alg(Iter begin, Iter end) {
        alg(begin, end, typename std::iterator_traits<Iter>::iterator_category());
    }
}

int main() {
    std::vector<int> v;
    std::list<int> l;

    alg(v.begin(), v.end());
    alg(l.begin(), l.end());
}

/* If you see implementation of std::advance(iterator, int n) in gcc, it relies on tag dispatch based on iterator category
 * If iterator category is
 * 1) input_iterator_tag: it uses a simple while loop to iterate n times.
 * 2) bidirectional_iterator_tag: it uses a simple while loop and iterates forward or backwards based on n being positive or negative
 * 3) random_access_iterator_tag: it uses "it += n", to straightaway jump to the requested location"
 *
 * Please read iterator_adaptors_5.cpp next
 */