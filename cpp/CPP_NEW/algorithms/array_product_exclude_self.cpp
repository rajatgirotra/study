/*
Iterate an integer array and find the product of all elements in the array excluding
the element being traversed. Return the resultant array.
YOU CANNOT USE THE DIVISION OPERATOR.

If we can use the division operator, we could just calculate the product of all elements in O(n).
Then for each element, we could just divide the product with that element.

But in this case, we can compute the product of the prefix array and postfix array of each element.
Then we can multiply the prefix and postfix products to get the answer.
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
#include <cstring>
#include <utility>
#include <ctime>
using namespace std;

template<size_t N>
void product_array_exclude_self(int (&arr)[N]) {
    int prefix_product = 1;
    int res[N]{};
    for(int i = 0; i < N; ++i) {
        res[i] = prefix_product;
        prefix_product *= arr[i];
    }

    int postfix_product = 1;
    for(int i = N-2; i >= 0; --i) {
        postfix_product *= arr[i+1];
        res[i] *= postfix_product;
    }


    cout << "Product Array exclude self: ";
    std::copy(begin(res), end(res), ostream_iterator<int>(cout, " "));

}

int main() {
    int arr[6] {};
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(-4, 4);
    auto gen = [dist = dist, engine = engine] () mutable {
        return dist(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    cout << "Elements: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;
    product_array_exclude_self(arr);
}
