we use super() to call the base class ctor. Just like we call this() for calling another ctor of the same class.
just like this(), super() must also be the first call inside a ctor.
the implicitly declared ctor of a class calls the default(no-arg) ctor of the base class.
if your base class doesnt have a default ctor, then you must call super() with the correct arguments as defined in the base
class ctor.

class Dog extends Animal {
    public Dog() {
        super(); // implicit ctor is like this.
    }
}