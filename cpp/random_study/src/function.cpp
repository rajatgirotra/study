#include <iostream>
#include <string>
#include <functional>

using namespace std;

class Double {
    double d;
public:
    explicit Double(double arg) : d(arg) {}

    explicit operator bool() {
        return d == 0;
    }
};

class UnknownClass;

union Erasure {
    void* mObject;
    const void* mConstObject;
    void (*mFunctionPtr)();
    void (UnknownClass::*mPtrMemberFunction)();
};


union ErasureData {

    void* access() { return &mUnused[0];}
    const void* access() const { return &mUnused[0]; }

    template <typename Type>
    Type& access() { return *static_cast<Type*>(access()); }

    template <typename Type>
    const Type& access() const { return *static_cast<const Type*>(access()); }

    Erasure mUnused;
    char mUsed[sizeof(Erasure)];
};

int main(int argc, char* argv[]) {
    std::function<bool()> b {[]() { return true;} };
    try {
        cout << b() << endl;
    } catch(const std::bad_function_call& e) {
        cerr << e.what() << endl;
    }

    Double d(0);
    if(d) {
        cout << "d is zero" << endl;
    } else {
        cout << "d is non zero" << endl;
    }

    cout << "sizeof(Erasure): " << sizeof(Erasure) << endl;
    cout << "sizeof(ErasureData): " << sizeof(ErasureData) << endl;
}