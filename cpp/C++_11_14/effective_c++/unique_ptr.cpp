/*
std::unique_ptr<T> or std::unique_ptr<T[]> - smart pointer to manage exclusive ownership of a resource.
When the unique_ptr object goes out of scope, the underlying resource is deleted. By default, unique_ptr calls delete on the underlying resource, but you can give your custom deleter. Good example is a factory method(see below). Note that the size of a unique_ptr class with default deleter is same as the size of raw pointer, so penalty for using unique_ptr. In case the deleter is a function pointer, the size of unique_ptr will increase by atleast the size of the function pointer, so that is why it is recommended to use function objects or stateless lambdas (lambdas which do not capture scope) as deleters as the compiler can directly stick the code in the function object in the d'tor of the unique_pointer so there is no increase in size.

Important
---------
std::unique_ptr<> cannot be copied, but can be moved. So we can actually put them into containers.
See up3.cpp
*/

#include <iostream>
#include <memory>
using namespace std;

#define CLASS(X) \
struct X { \
    virtual ~X() { \
        cout << #X"::~"#X << endl;\
    }\
    X() {\
        cout << #X"::"#X << endl;\
    }\
};

#define SUBCLASS(X,Y) \
    struct X : public Y { \
    virtual ~X() { \
        cout << #X"::~"#X << endl;\
    }\
    X() {\
        cout << #X"::"#X << endl;\
    }\
};

CLASS(Investment)
SUBCLASS(Stock,Investment)
SUBCLASS(Bond,Investment)
SUBCLASS(RealEstate,Investment)

/* Write generic factory method based on variadic templates, perfect forwarding */
// template <typename... Args>
// std::unique_ptr<Investment> makeInvestment(int type, Args&&... args) {
//     if (type == 0) {
//         return std::make_unique<Stock>(std::forward<Args>(args)...);
//     } else if (type == 1) {
//         return std::make_unique<Bond>(std::forward<Args>(args)...);
//     } else {
//         return std::make_unique<RealEstate>(std::forward<Args>(args)...);
//     }
// }

// Same as above, but with a custome deleter
// Create a deleter first in C++11 as we need its type to specify in the return type of the makeInvestment function
auto delInv = [](Investment* pInvestment) {
                 cout << "Deleter called. Deleting..." << endl;
                 delete pInvestment;
               };

template <typename... Args>
auto makeInvestment(int type, Args&&... args) -> std::unique_ptr<Investment, decltype(delInv)> {
    std::unique_ptr<Investment, decltype(delInv)> pInv {nullptr, delInv};
    if (type == 0) {
        pInv.reset(new Stock(std::forward<Args>(args)...));
    } else if (type == 1) {
        pInv.reset(new Bond(std::forward<Args>(args)...));
    } else {
        pInv.reset(new RealEstate(std::forward<Args>(args)...));
    }
    return pInv;
}

int main () {
    auto pInv = makeInvestment(10);
    return 0;
}
