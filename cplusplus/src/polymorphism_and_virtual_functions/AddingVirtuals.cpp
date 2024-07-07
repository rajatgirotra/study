/*

Inheritance and the VTABLE

You can imagine what happens when you perform inheritance and override some of the virtual functions. The compiler creates a new VTABLE for your new class, and it inserts your new function addresses using the base-class function addresses for any virtual functions you don.t override. One way or another, for every object that can be created (that is, its class has no pure virtuals) there.s always a full set of function addresses in the VTABLE, so you.ll never be able to make a call to an address that isn.t there (which would be disastrous).

But what happens when you inherit and add new virtual functions in the derived class? Here.s a simple example:

*/

    //: C15:AddingVirtuals.cpp
    // Adding virtuals in derivation
    #include <iostream>
    #include <string>
    using namespace std;

    class Pet {
      string pname;
    public:
      Pet(const string& petName) : pname(petName) {}
      virtual string name() const { return pname; }
      virtual string speak() const { return ""; }
      virtual ~Pet() {}
    };

    class Dog : public Pet {
      //string name;
    public:
      Dog(const string& petName) : Pet(petName) {}
      // New virtual function in the Dog class:
      virtual string sit() const {
        return Pet::name() + " sits";
      }
      string speak() const { // Override
        return Pet::name() + " says 'Bark!'";
      }
    };

    int main() {
      Pet* p[] = {new Pet("generic"),new Dog("bob")};
      cout << "p[0]->speak() = "
           << p[0]->speak() << endl;
      cout << "p[1]->speak() = "
           << p[1]->speak() << endl;
     cout << "p[1]->sit() = "
          << (static_cast<Dog*>(p[1]))->sit() << endl; // Illegal
    } ///:~

/*

The class Pet contains a two virtual functions: speak( ) and name( ). Dog adds a third virtual function called sit( ), as well as overriding the meaning of speak( ). A diagram will help you visualize what.s happening. Here are the VTABLEs created by the compiler for Pet and Dog:

Notice that the compiler maps the location of the speak( ) address into exactly the same spot in the Dog VTABLE as it is in the Pet VTABLE. Similarly, if a class Pug is inherited from Dog, its version of sit( ) would be placed in its VTABLE in exactly the same spot as it is in Dog. This is because (as you saw with the assembly-language example) the compiler generates code that uses a simple numerical offset into the VTABLE to select the virtual function. Regardless of the specific subtype the object belongs to, its VTABLE is laid out the same way, so calls to the virtual functions will always be made the same way.

In this case, however, the compiler is working only with a pointer to a base-class object. The base class has only the speak( ) and name( ) functions, so those is the only functions the compiler will allow you to call. How could it possibly know that you are working with a Dog object, if it has only a pointer to a base-class object? That pointer might point to some other type, which doesn.t have a sit( ) function. It may or may not have some other function address at that point in the VTABLE, but in either case, making a virtual call to that VTABLE address is not what you want to do. So the compiler is doing its job by protecting you from making virtual calls to functions that exist only in derived classes.

There are some less-common cases in which you may know that the pointer actually points to an object of a specific subclass. If you want to call a function that only exists in that subclass, then you must cast the pointer. You can remove the error message produced by the previous program like this:

      ((Dog*)p[1])->sit()

Here, you happen to know that p[1] points to a Dog object, but in general you don.t know that. If your problem is set up so that you must know the exact types of all objects, you should rethink it, because you.re probably not using virtual functions properly. However, there are some situations in which the design works best (or you have no choice) if you know the exact type of all objects kept in a generic container. This is the problem of run-time type identification (RTTI).

*/
