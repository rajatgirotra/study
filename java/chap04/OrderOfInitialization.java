// Read MR4.txt

//: c04:OrderOfInitialization.java
// Demonstrates initialization order.
// When the constructor is called to create a
// Tag object, you'll see a message:
class Tag {
   Tag(int marker) {
      System.out.println("Tag(" + marker + ")");
   }
}
class Card {
   Tag t1 = new Tag(1); // Before constructor
   Card() {
      // Indicate we're in the constructor:
      System.out.println("Card()");
      t3 = new Tag(33); // Reinitialize t3
   }
   Tag t2 = new Tag(2); // After constructor
   void f() {
      System.out.println("f()");
   }
   Tag t3 = new Tag(3); // At end
}

public class OrderOfInitialization {
   public static void main(String[] args) {
      Card t = new Card();
      t.f(); // Shows that construction is done
   }
} ///:~
