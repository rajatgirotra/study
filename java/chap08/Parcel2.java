/*
Please read TestParcel1.java first
More typically, an outer class will have a method that returns a reference
to an inner class, like this:
*/

import java.util.*;

public class Parcel2 {
	class Contents {
		private int i;
		Contents(int i) {
			this.i = i;
		}
		public String toString() {
			return Integer.toString(i);
		}		
	}

	class Destination {
		private String s;
		Destination(String s) {
			this.s = s;
		}
		public String toString() {
			return s;
		}
	}

	public Contents contents(int i) {
		return new Contents(i);
	}

	public Destination dest(String s) {
		return new Destination(s);
	}
	public void ship(String desti) {
		Contents c = contents(1);
		Destination d = dest(desti);
		System.out.println("Shipping " + c + " to " + d);
	}
	
	public static void main(String[] args) {
		Parcel2 pc2 = new Parcel2();
		pc2.ship("Amsterdam");
	}
}

/*
 * Please read TestParcel.java next
 */
