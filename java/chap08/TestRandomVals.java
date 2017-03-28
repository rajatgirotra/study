/*
 * Please read TestRandVals.java first
 * Even if you have two classes implementing the interface whose public static final variables are
 * assigned a value at run time, in both the classes, you'll see the same values of the variables.
 */

import c08.RandVals;

class ABC implements RandVals {
	public void display() {
		System.out.println(ABC.i);
		System.out.println(ABC.l);
		System.out.println(ABC.f);
		System.out.println(ABC.d);	
	}
}

class XYZ implements RandVals {
	public void display() {
		System.out.println(XYZ.i);
		System.out.println(XYZ.l);
		System.out.println(XYZ.f);
		System.out.println(XYZ.d);	
	}
}
public class TestRandomVals {
	public static void main(String[] args) {
		ABC abc = new ABC();
		abc.display();
		System.out.println();
		XYZ xyz = new XYZ();
		xyz.display();
	}
}

/*
Please read TestBed.java next
*/