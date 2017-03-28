/*
 * Parcel10.java first
 * You cannot make an object of a non-static inner class unless
 * you have an object of the enclosing class. See the unusual new syntax below. 
 */
import java.util.*;

public class Parcel11 {
	private long l;
	private static double d;
	Random rand = new Random();
	Parcel11() {
		l = rand.nextLong();
		d = rand.nextDouble();
	}
	class Contents {
		private int i;
		public Contents() {
			i = 11;
			System.out.println("Contents: Outer long value = " + Parcel11.this.l);
			System.out.println("Contents: Outer long value = " + Parcel11.this.d);
			// See above how you can access the outer class member using the CLASSNAME.this.MEMBERFIELD construct.
		}
	}
	
	class Destination {
		private String label;
		public Destination(String whereTo) {
			label = whereTo;
			System.out.println("Destination: Outer long value = " + l);
			System.out.println("Destination: Outer long value = " + d);
		}
	}
	
	public static void main(String[] args) {
		Parcel11 p11 = new Parcel11();
		Parcel11.Contents c = p11.new Contents(); // This might seem a bit unusual.
		Parcel11.Destination d = p11.new Destination("Sydney"); // This might seem a bit unusual too.
	}
}

/*
Thus, it’s not possible to create an object of the inner class unless you
already have an object of the outer class. This is because the object of the
inner class is quietly connected to the object of the outer class that it was
made from. However, if you make a nested class (a static inner class),
then it doesn’t need a reference to the outer class object (as in Parcel10.java).

Sequence.java next
*/
