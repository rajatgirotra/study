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
