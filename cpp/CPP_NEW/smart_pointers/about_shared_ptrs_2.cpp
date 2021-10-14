/*
 * std::shared_ptr declaration is also very trivial. the deleter is not part of the template unlike std::unique_ptr.
 *
 * template <typename T>
 * struct shared_ptr {
 * };
 *
 * There is no full/partial specialization for array types but starting from C++17, std::shared_ptr can also handle array types.
 * i.e. the deleter will call delete[] for array types automatically.
 *
 * before c++17, you had to give your own custom deleter for array types. example:
 *
 * std::shared_ptr<Test> p(new Test[10], [](Test* p) { delete[] p; });
 *
 * std::make_shared<>() still doesnt work for array types in C++17, only in C++20.
 * so "auto ptr = std::make_shared<Test[]>(10); // only works with C++20.
 *
 * class Base {};
 * class Derived : public Base{};
 *
 * auto spBase = std::shared_ptr<Base>(new Derived);
 * assert(spBase.use_count() == 1); // trivial.
 *
 * But
 * Derived* d = dynamic_cast<Derived*>(spBase.get()); // will return the underlying pointer but use_count() is still 1.
 * Not very good. se dynamic_pointer_cast<> is better
 *
 * std::shared_ptr<Derived> spDerived = std::dynamic_pointer_cast<Base>(spBase);
 *
 */

int main() {

}
