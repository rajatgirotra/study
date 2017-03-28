/*

Private inheritance

You may wonder what the purpose of private inheritance is, because the alternative of using composition to create a private object in the new class seems more appropriate. private inheritance is included in the language for completeness, but if for no other reason than to reduce confusion, you.ll usually want to use composition rather than private inheritance. However, there may occasionally be situations where you want to produce part of the same interface as the base class and disallow the treatment of the object as if it were a base-class object. private inheritance provides this ability.
Publicizing privately inherited members

When you inherit privately, all the public members of the base class become private. If you want any of them to be visible, just say their names (no arguments or return values) along with the using keyword in the public section of the derived class:

*/

    //: C14:PrivateInheritance.cpp
    class Pet {
    public:
      char eat() const { return 'a'; }
      int speak() const { return 2; }
      float sleep() const { return 3.0; }
      float sleep(int) const { return 4.0; }
    };

    class Goldfish : private Pet { // Private inheritance
    public:
      using Pet::eat; // Name publicizes member
      using Pet::sleep; // Both overloaded members exposed
    };

    int main() {
      Goldfish bob;
      bob.eat();
      bob.sleep();
      bob.sleep(1);
      bob.speak();// Error: private member function
    } ///:~

/*

Thus, private inheritance is useful if you want to hide part of the functionality of the base class.

Notice that giving exposing the name of an overloaded function exposes all the versions of the overloaded function in the base class.

You should think carefully before using private inheritance instead of composition; private inheritance has particular complications when combined with runtime type identification

*/
