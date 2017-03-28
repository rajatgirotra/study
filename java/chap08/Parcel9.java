/*
 * Parcel8.java first
 */
import java.util.*;
import c08.Destination;

public class Parcel9 {
	public Destination dest(final String dest, final float price) {
		return new Destination() {
			private String s = dest;  // ---->> line A			
			private int cost;
			{
				cost = Math.round(price);
				if(cost > 100) {
					System.out.println("Cannot send parcel to " + readLabel() + "..!! cost of " + cost + "  is too high");
				}
			}
			
			public String readLabel() {
				return s;
			}
		};
	}
	
	public static void main(String[] args) {
		Parcel9 pc9 = new Parcel9();
		Destination d = pc9.dest("Switzerland", 101.78f);
	}
}

/*
So in effect, an
instance initializer is the constructor for an anonymous inner class. Of
course, it’s limited; you can’t overload instance initializers so you can have
only one of these constructors.

Also if i place line A after the initializer, then s gets initialised after the initialiser code has run.
move line A after the initialiser & see for yourself. 
So the behavior of the initialiser is not exactly as the c'tor for a class.

Parcel10.java next
*/
