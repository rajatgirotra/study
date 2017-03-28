/*
   Normally, when you say this, it is in the sense of this object or the
   current object, and by itself it produces the reference to the current
   object. In a constructor, the this keyword takes on a different meaning
   when you give it an argument list: it makes an explicit call to the
   constructor that matches that argument list. Thus you have a
   straightforward way to call other constructors.
 */

//: c04:Flower.java
// Calling constructors with "this."
public class Flower {
  int petalCount = 0;
  String s = new String("null");

  Flower(int petals) {
    petalCount = petals;
    System.out.println(
        "Constructor w/ int arg only, petalCount= "
        + petalCount);
  }
  Flower(String ss) {
    System.out.println(
        "Constructor w/ String arg only, s=" + ss);
    s = ss;
  }
  Flower(String s, int petals) {
    this(petals);
    //! this(s); // Can't call two!
    this.s = s; // Another use of "this"
    System.out.println("String & int args");
  }
  Flower() {
    this("hi", 47);
    System.out.println("default constructor (no args)");
  }
  void print() {
    //! this(11); // Not inside non-constructor!
    System.out.println(
        "petalCount = " + petalCount + " s = "+ s);
  }
  public static void main(String[] args) {
    Flower x = new Flower();
    x.print();
  }
} ///:~

/*

The constructor Flower(String s, int petals) shows that, while you can
call one constructor using this, you cannot call two. In addition, the
constructor call must be the first thing you do or youll get a compiler
error message.

This example also shows another way youll see this used. Since the name
of the argument s and the name of the member data s are the same,
theres an ambiguity. You can resolve it by saying this.s to refer to the
member data. Youll often see this form used in Java code, and its used in
numerous places in this book.

In print( ) you can see that the compiler wont let you call a constructor
from inside any method other than a constructor.

*/
