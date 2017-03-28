//: c06:FinalData.java
// The effect of final on fields.
import java.util.*;
class Value {
	int i; // Package access
	public Value(int i) { this.i = i; }
}
public class FinalData {
	private static Random rand = new Random();
	private String id;

	public FinalData(String id) { this.id = id; }

	// Can be compile-time constants:
	private final int VAL_ONE = 9;
	private static final int VAL_TWO = 99;

	// Typical public constant:
	public static final int VAL_THREE = 39;

	// Cannot be compile-time constants:
	private final int i4 = rand.nextInt(20);
	static final int i5 = rand.nextInt(20);
	private Value v1 = new Value(11);
	private final Value v2 = new Value(22);
	private static final Value v3 = new Value(33);

	// Arrays:
	private final int[] a = { 1, 2, 3, 4, 5, 6 };

	public String toString() {
		return id + ": " + "i4 = " + i4 + ", i5 = " + i5;
	}
	public static void main(String[] args) {
		FinalData fd1 = new FinalData("fd1");

		//! fd1.VAL_ONE++; // Error: can't change value
		fd1.v2.i++; // Object isn't constant!

		fd1.v1 = new Value(9); // OK -- not final

		for(int i = 0; i < fd1.a.length; i++)
			fd1.a[i]++; // Object isn't constant!
		
		//! fd1.v2 = new Value(0); // Error: Can't
		//! fd1.v3 = new Value(1); // change reference
		//! fd1.a = new int[3];

		System.out.println(fd1);

		System.out.println("Creating new FinalData");
		FinalData fd2 = new FinalData("fd2");
		System.out.println(fd1);
		System.out.println(fd2);
	}
} ///:~

/*
   Since VAL_ONE and VAL_TWO are final primitives with compiletime
   values, they can both be used as compile-time constants and are not
   different in any important way. VAL_THREE is the more typical way
   youll see such constants defined: public so theyre usable outside the
   package, static to emphasize that theres only one, and final to say that
   its a constant. Note that final static primitives with constant initial
   values (that is, compile-time constants) are named with all capitals by
   convention, with words separated by underscores (This is just like C
   constants, which is where the convention originated.) Also note that i5
   cannot be known at compile time, so it is not capitalized. Feedback
   Just because something is final doesnt mean that its value is known at
   compile time. This is demonstrated by initializing i4 and i5 at run time
   using randomly generated numbers. This portion of the example also
   shows the difference between making a final value static or non-static.
   This difference shows up only when the values are initialized at run time,
   since the compile-time values are treated the same by the compiler. (And
   presumably optimized out of existence.) The difference is shown when
   you run the program. Note that the values of i4 for fd1 and fd2 are
   unique, but the value for i5 is not changed by creating the second
   FinalData object. Thats because its static and is initialized once upon
   loading and not each time a new object is created. Feedback
   The variables v1 through v3 demonstrate the meaning of a final
   reference. As you can see in main( ), just because v2 is final doesnt
   mean that you cant change its value. Because its a reference, final means
   that you cannot rebind v2 to a new object. You can also see the same
   meaning holds true for an array, which is just another kind of reference.
   (There is no way that I know of to make the array references themselves
   final.) Making references final seems less useful than making primitives
   final.

As you can see in main( ), just because v2 is final doesnt
mean that you cant change its value. Because its a reference, final means
that you cannot rebind v2 to a new object. You can also see the same
meaning holds true for an array, which is just another kind of reference.
 */
