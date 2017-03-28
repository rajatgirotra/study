/*
   It is very common to use composition and inheritance together. The
   following example shows the creation of a more complex class, using both
   inheritance and composition, along with the necessary constructor
initialization:
 */

//: c06:PlaceSetting.java
// Combining composition & inheritance.

import java.util.*;

class Plate {
	Plate(int i) {
		System.out.println("Plate constructor");
	}
}
class DinnerPlate extends Plate {
	DinnerPlate(int i) {
		super(i);
		System.out.println("DinnerPlate constructor");
	}
}
class Utensil {
	Utensil(int i) {
		System.out.println("Utensil constructor");
	}
}
class Spoon extends Utensil {
	Spoon(int i) {
		super(i);
		System.out.println("Spoon constructor");
	}
}
class Fork extends Utensil {
	Fork(int i) {
		super(i);
		System.out.println("Fork constructor");
	}
}
class Knife extends Utensil {
	Knife(int i) {
		super(i);
		System.out.println("Knife constructor");
	}
}
// A cultural way of doing something:
class Custom {
	Custom(int i) {
		System.out.println("Custom constructor");
	}
}
public class PlaceSetting extends Custom {
	private Spoon sp;
	private Fork frk;
	private Knife kn;
	private DinnerPlate pl;
	public PlaceSetting(int i) {
		super(i + 1);
		sp = new Spoon(i + 2);
		frk = new Fork(i + 3);
		kn = new Knife(i + 4);
		pl = new DinnerPlate(i + 5);
		System.out.println("PlaceSetting constructor");
	}
	public static void main(String[] args) {
		PlaceSetting x = new PlaceSetting(9);
	}
} ///:~

/*
   While the compiler forces you to initialize the base classes, and requires
   that you do it right at the beginning of the constructor, it doesnt watch
   over you to make sure that you initialize the member objects, so you must
   remember to pay attention to that.
 */
