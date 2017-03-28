/* Static Nested class:
 * Parcel9.java first
 * an inner class declared as static is called a static nested class.
 * Ideally an ordinary inner class keeps a hidden reference to an object 
 * of the outer class. But this is NOT TRUE for static nested classes.
 * 
 *  a static nested class object can be created without creating an object of the enclosing class
 *  also a nested class cannot access non-static members of the enclosing class.
 */

import java.util.*;
import c08.Destination;
import c08.Contents;

public class Parcel10 {
	public static class ParcelContents implements Contents {
		private int i = 11;
		public int value() {
			return i;
		}
	}
	
	public static class ParcelDestination implements Destination {
		private String label;
		public ParcelDestination(String whereTo) {
			label = whereTo;
		}
		public String readLabel() {
			return label;			
		}
	}
	
	public static Contents getContents() {
		return new ParcelContents();
	}
	
	public static Destination getDestination(String whereTo) {
		return new ParcelDestination(whereTo);
	}
	
	public static void main(String[] args) {
		Contents c = getContents();
		Destination d = getDestination("Tanzania");
	}
}

/*
Parcel11.java next
*/