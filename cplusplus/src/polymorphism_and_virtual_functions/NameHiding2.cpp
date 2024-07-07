/*

Overloading & overriding

In Chapter 14, you saw that redefining an overloaded function in the base class hides all of the other base-class versions of that function. When virtual functions are involved the behavior is a little different. Consider a modified version of the NameHiding.cpp example from Chapter 14:

*/

    //: C15:NameHiding2.cpp
    // Virtual functions restrict overloading
    #include <iostream>
    #include <string>
    using namespace std;

    class Base {
    public:
      virtual int f() const { 
        cout << "Base::f()\n"; 
        return 1; 
      }
      virtual void f(string) const {}
      virtual void g() const {}
      virtual ~Base() {}
    };

    class Derived1 : public Base {
    public:
      void g() const {}
    };

    class Derived2 : public Base {
    public:
      // Overriding a virtual function:
      int f() const { 
        cout << "Derived2::f()\n"; 
        return 2;
      }
    };

    class Derived3 : public Base {
    public:
      // Cannot change return type:
      //! void f() const{ cout << "Derived3::f()\n";}
    };

    class Derived4 : public Base {
    public:
      // Change argument list:
      int f(int) const { 
        cout << "Derived4::f()\n"; 
        return 4; 
      }
    };

    int main() {
      string s("hello");
      Derived1 d1;
      int x = d1.f();
      d1.f(s);
      Derived2 d2;
      x = d2.f();
    //!  d2.f(s); // string version hidden
      Derived4 d4;
      x = d4.f(1);
    //!  x = d4.f(); // f() version hidden
    //!  d4.f(s); // string version hidden
      Base& br = d4; // Upcast
    //!  br.f(1); // Derived version unavailable
      br.f(); // Base version available
      br.f(s); // Base version abailable
    } ///:~

/*

The first thing to notice is that in Derived3, the compiler will not allow you to change the return type of an overridden function (it will allow it if f( ) is not virtual). This is an important restriction because the compiler must guarantee that you can polymorphically call the function through the base class, and if the base class is expecting an int to be returned from f( ), then the derived-class version of f( ) must keep that contract or else things will break.

The rule shown in Chapter 14 still works: if you override one of the overloaded member functions in the base class, the other overloaded versions become hidden in the derived class. In main( ) the code that tests Derived4 shows that this happens even if the new version of f( ) isn.t actually overriding an existing virtual function interface . both of the base-class versions of f( ) are hidden by f(int). However, if you upcast d4 to Base, then only the base-class versions are available (because that.s what the base-class contract promises) and the derived-class version is not available (because it isn.t specified in the base class).

*/
