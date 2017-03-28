#include <boost/signals2.hpp>
#include <iostream>
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

/* Creating a combiner which a function object passed as a second template
argument when creating a signal. The result_type should be the same as the
return type of the signal you are creating
The function object receives a couple of iterators - deferecing them automatically
calls the slots
In our case we return the maximum value from all of our slot calls.
*/
template <typename ReturnType>
struct combiner {
    typedef ReturnType result_type;

    template <typename InputIterator>
    result_type operator() (InputIterator first, InputIterator last) {
        result_type max {};
        while (first != last) {
            result_type res = *first++;
            max = (res > max ? res : max);
        }
        return max;
    }
};

int main(int argc, char *argv[]) {
    boost::signals2::signal<float(float, float), combiner<float> > sig;

    // add all slots
    sig.connect(add);
    sig.connect(sub);
    sig.connect(mul);
    sig.connect(divi);

    cout << sig(5.0, 3.0) << endl;
    return 0;
}

/*
Note that if you dont provide a default combiner, the default combiner
returns a boost::optional<> with the value return value of the last slot.
*/
