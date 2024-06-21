/*

You can refer to a name within a namespace in three ways: by specifying the name using the scope resolution operator, with a using directive to introduce all names in the namespace, or with a using declaration to introduce names one at a time.


Scope resolution
Any name in a namespace can be explicitly specified using the scope resolution operator in the same way that you can refer to the names within a class:

*/

//: C10:ScopeResolution.cpp
namespace X {
  class Y {
    static int i;
  public:
    void f();
  };
  class Z;
  void func();
}
int X::Y::i = 9;
class X::Z {
  int u, v, w;
public:
  Z(int i);
  int g();
}; 
X::Z::Z(int i) { u = v = w = i; }
int X::Z::g() { return u = v = w = 0; }
void X::func() {
  X::Z a(1);
  a.g();
}

int main(){} ///:~

