Access modifiers for methods

public, private, <EMPTY>
final (means a method cannot be overriden)
abstract (means method body is ommitted)
static (a static method)
default (only applicable to an interface)
native (this means that the method body will be implemented in some other language like C. Not used very often in Java)
synchronized (means multiple threads need to take turns to execute the method body. basically provides mutual exclusion)

abstract class Animal {}; // an abstract class is an incomplete class. So cannot instantiate it.

public abstract void move(); // an abstract method. Must be in an abstract class or interface