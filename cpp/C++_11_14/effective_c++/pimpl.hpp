#pragma once

#include <memory>

class MyPimpl {
private:
    struct Impl;
    using ImplType = std::unique_ptr<Impl>;
    ImplType impl_;

public:
    MyPimpl();
    ~MyPimpl();

    MyPimpl(MyPimpl&&);
    MyPimpl& operator=(MyPimpl&&);

    void sayHello();
};
