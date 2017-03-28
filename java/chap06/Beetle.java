//: c06:Beetle.java
// The full process of initialization.
import java.util.*; 
class Insect {
	private int i = 9;
	protected int j;
	Insect() {
		System.out.println("i = " + i + ", j = " + j);
		j = 39;
	}
	private static int x1 =
		print("static Insect.x1 initialized");
	static int print(String s) {
		System.out.println(s);
		return 47;
	}
}
public class Beetle extends Insect {
	private int k = print("Beetle.k initialized");
	public Beetle() {
		System.out.println("k = " + k);
		System.out.println("j = " + j);
	}
	private static int x2 =
		print("static Beetle.x2 initialized");
	public static void main(String[] args) {
		System.out.println("Beetle constructor");
		Beetle b = new Beetle();
	}
}

/*
   The first thing that happens when you run Java on Beetle is that you try
   to access Beetle.main( ) (a static method), so the loader goes out and
   finds the compiled code for the Beetle class (this happens to be in a file
   called Beetle.class). In the process of loading it, the loader notices that it
   has a base class (thats what the extends keyword says), which it then
   loads. This will happen whether or not youre going to make an object of
   that base class. (Try commenting out the object creation to prove it to
   yourself.)


   If the base class has a base class, that second base class would then be
   loaded, and so on. Next, the static initialization in the root base class (in
   this case, Insect) is performed, and then the next derived class, and so
   on. This is important because the derived-class static initialization might
   depend on the base class member being initialized properly. Feedback
   At this point, the necessary classes have all been loaded so the object can
   be created. First, all the primitives in this object are set to their default
   values and the object references are set to nullthis happens in one fell
   swoop by setting the memory in the object to binary zero. Then the baseclass
   constructor will be called. In this case the call is automatic, but you
   can also specify the base-class constructor call (as the first operation in
   the Beetle( ) constructor) using super. The base class construction goes
   through the same process in the same order as the derived-class
   constructor. After the base-class construction completes, the instance
   variables are initialized in textual order. Finally, the rest of the body of the
   constructor is executed.
 */
