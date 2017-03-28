/*
Class has many interesting methods, demonstrated in the following example:
 */

// Testing class Class.
package c10;
interface HasBatteries {}
interface Waterproof {}
interface Shoots {}
class Toy {
	// Comment out the following default constructor
	// to see NoSuchMethodError from (*1*)
	Toy() {}
	Toy(int i) {}
}
class FancyToy extends Toy

implements HasBatteries, Waterproof, Shoots {
	FancyToy() { super(1); }
}
public class ToyTest {

	static void printInfo(Class cc) {
		System.out.println("Class name: " + cc.getName() +
				" is interface? [" + cc.isInterface() + "]");
	}
	public static void main(String[] args) {
		Class c = null;
		try {
			c = Class.forName("c10.FancyToy");
		} catch(ClassNotFoundException e) {
			System.out.println("Can't find FancyToy");
			System.exit(1);
		}
		printInfo(c);
		Class[] faces = c.getInterfaces();
		for(int i = 0; i < faces.length; i++)
			printInfo(faces[i]);
		Class cy = c.getSuperclass();
		Object o = null;
		try {
			// Requires default constructor:
			o = cy.newInstance(); // (*1*)
		} catch(InstantiationException e) {
			System.out.println("Cannot instantiate");
			System.exit(1);
		} catch(IllegalAccessException e) {
			System.out.println("Cannot access");
			System.exit(1);
		}
		printInfo(o.getClass());

	}
}