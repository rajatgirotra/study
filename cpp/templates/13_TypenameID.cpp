//: C05:TypenamedID.cpp {-bor}
// Uses 'typename' as a prefix for nested types.
 
template<class T> class X {
  // Without typename, you should get an error:
   typename T::id i;
public:
  void f() { i.g(); }
};
 
class Y {
public:
  class id {
  public:
    void g() {}
  };
};
 
int main() {
  X<Y> xy;
  xy.f();
} ///:~

