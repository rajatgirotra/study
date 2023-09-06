Read SmartKitchen and Printer first.

Java has a keyword called "var". This is same as "auto" keyword in C++.

var theMovie = Movie.getMovie(args...);

Object.getClass() --> returns you the run-time class type. I.e. the derived type when using polymorphism.
getClass() returns an object of java.lang.Class<T>

Object unknownObject = Movie.getMovie(args...);
if (unknownObject instanceof Adventure) {
    ((Adventure)unknownObject).watchAdventure();
}

// from JDK 16 (smarter way of using instanceof)
if (unknownObject instanceof Adventure adventure) {
    adventure.watchAdventure();
}
when the if condition is true, adventure is already available, otherwise we dont use it.

