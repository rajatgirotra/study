#include <boost/signals2.hpp>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;

float add(float a, float b) {
    return a + b;
}

float sub(float a, float b) {
    return a - b;
}

float mul(float a, float b) {
    return a * b;
}

float divi(float a, float b) {
    return a / b;
}

/* Creating a combiner which a function object which returns
a vector of values returned from all the slots.
*/
template <typename Container>
struct combiner {
    typedef Container result_type;

    template <typename InputIterator>
    result_type operator() (InputIterator first, InputIterator last) {
        result_type container;
        while (first != last) {
            container.push_back(*first++);
        }
        return container;
    }
};

int main(int argc, char *argv[]) {
    boost::signals2::signal<float(float, float), combiner<std::vector<float>>> sig;

    // add all slots
    sig.connect(add);
    sig.connect(sub);
    sig.connect(mul);
    sig.connect(divi);

    auto values = sig(5.0, 3.0);
    for (auto value : values) {
        cout << value << endl;
    }
    return 0;
}

