/*

Please read TestBed.java first

It’s possible to place a class definition within another class definition. This
is called an inner class. The inner class is a valuable feature because it
allows you to group classes that logically belong together and to control
the visibility of one within the other. However, it’s important to
understand that inner classes are distinctly different from composition.
 */

import java.util.*;
public class Parcel1 {
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
		public String toString(){
			return s;
		}
	}
	
	void ship(int i, String s) {
		Contents c = new Contents(i);
		Destination d = new Destination(s);
		System.out.println("Sending " + c + " to " + d);
	}
	
	public static void main(String[] args) {
		Parcel1 pc1 = new Parcel1();
		pc1.ship(34, "Tanzania");
	}
}

/*
Please read TestParcel2.java next
*/