#include "pimpl.hpp"
#include <iostream>
using namespace std;


struct MyPimpl::Impl {
    void sayHello() {
        cout << "Hello\n";
    }
};

MyPimpl::MyPimpl() : impl_(new Impl) {
}

MyPimpl::~MyPimpl() = default;

MyPimpl::MyPimpl(MyPimpl&&) = default;
MyPimpl& MyPimpl::operator=(MyPimpl&&) = default;


void MyPimpl::sayHello() {
    impl_->sayHello();
}
