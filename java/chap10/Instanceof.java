/* Understanding how to use instanceof in JAVA */
/* Lesson 1:
 * 'x' is a base class reference pointing to any of the derived class object:
 * eg: Base class is "Dog" and derived class is Pug; then;
 * (x instanceof Dog) will always be true.
 * 
 * Lesson 2: If you have an another derived class called "Labrador";
 * then (x instance Labrador) will be true if and only if Dog x = new Labrador() is defined.
 * This is called a safe downcast as shown below. 
 * 
 * So basically instanceof can be used to perform a safe-downcast; otherwise you might get a 
 * ClassCastException.
 */

import java.util.*;
/*
class Dog {
	public void describe() {
		System.out.println("I am a Dog object");
	}
}
class Pug extends Dog {
	public void describe() {
		System.out.println("I am a Pug object. I am a kind of Dog");
	}
}

class Labrador extends Dog {
	public void describe() {
		System.out.println("I am a Labrador object. I am a kind of Dog");
	}
	
	public void bark() {
		System.out.println("Labradors bark very loud");
	}
}
public class Instanceof {
	public static void main(String[] args) {
		Dog x = new Labrador();
		if(x instanceof Labrador) {
			((Labrador)x).bark();
		}
		
		Dog y = new Pug();
		if(y instanceof Dog) {
			y.describe();
		}
	}
}
*/