/* read unique_ptr.cpp first. With C++14, we can make the custom deleter part of makeInvestment as C++14 supports auto return type deduction. Lets see
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


template <typename... Args>
auto makeInvestment(int type, Args&&... args) {
    auto delInv = [](Investment* pInvestment) {
                 cout << "Deleter called. Deleting..." << endl;
                 delete pInvestment;
               };
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
