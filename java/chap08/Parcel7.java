//Parcel6.java first

//: c08:Parcel7.java
// An anonymous inner class that calls
// the base-class constructor.
/* In the anonymous inner class, Contents is created using a default
constructor. The following code shows what to do if your base class needs
a constructor with an argument.
*/

import c08.Wrapping;
public class Parcel7 {
	public Wrapping wrap(int x) {
		// Base constructor call:
		return new Wrapping(x) { // Pass constructor argument.
			public int value() {
				return super.value() * 47;
			}
		}; // Semicolon required
	}
	public static void main(String[] args) {
		Parcel7 p = new Parcel7();
		Wrapping w = p.wrap(10);
		w.display();
		System.out.println(w.value());
	}
}

/*
That is, you simply pass the appropriate argument to the base-class
constructor, seen here as the x passed in new Wrapping(x).

Parcel8.java next
*/
