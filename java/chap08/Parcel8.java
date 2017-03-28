/*
 * Parcel7.java first
 */

//: c08:Parcel8.java
// An anonymous inner class that performs
// initialization. A briefer version of Parcel5.java.
import c08.Destination;
public class Parcel8 {
	// Argument must be final to use inside
	// anonymous inner class:
	public Destination dest(final String dest) { // The argument dest must be final.
		return new Destination() {
			private String label = dest; // this is the initialization.
			public String readLabel() { return label; }
		};
	}
	public static void main(String[] args) {
		Parcel8 p = new Parcel8();
		Destination d = p.dest("Tanzania");
	}
}

/*
If you’re defining an anonymous inner class and want to use an object
that’s defined outside the anonymous inner class, the compiler requires
that the argument reference be final, like the argument to dest( ). If you
forget, you’ll get a compile-time error message.

Parcel9.java next
*/