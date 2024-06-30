/*
Choosing composition vs. inheritance
Both composition and inheritance place subobjects inside your new class. Both use the constructor initializer list to construct these subobjects. You may now be wondering what the difference is between the two, and when to choose one over the other.
Composition is generally used when you want the features of an existing class inside your new class, but not its interface. That is, you embed an object to implement features of your new class, but the user of your new class sees the interface you.ve defined rather than the interface from the original class. To do this, you follow the typical path of embedding private objects of existing classes inside your new class.
Occasionally, however, it makes sense to allow the class user to directly access the composition of your new class, that is, to make the member objects public. The member objects use access control themselves, so this is a safe thing to do and when the user knows you.re assembling a bunch of parts, it makes the interface easier to understand. A Car class is a good example:
*/

    //: C14:Car.cpp
    // Public composition

    class Engine {
    public:
      void start() const {}
      void rev() const {}
      void stop() const {}
    };

    class Wheel {
    public:
      void inflate([[maybe_unused]] int psi) const {}
    };

    class Window {
    public:
      void rollup() const {}
      void rolldown() const {}
    };

    class Door {
    public:
      Window window;
      void open() const {}
      void close() const {}
    };

    class Car {
    public:
      Engine engine;
      Wheel wheel[4];
      Door left, right; // 2-door
    };

    int main() {
      Car car;
      car.left.window.rollup();
      car.wheel[0].inflate(72);
    } ///:~

/*

With a little thought, you.ll also see that it would make no sense to compose a Car using a .vehicle. object . a car doesn.t contain a vehicle, it is a vehicle. The is-a relationship is expressed with inheritance, and the has-a relationship is expressed with composition.

*/
