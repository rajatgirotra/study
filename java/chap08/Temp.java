/*
 * Please read NestingInterfaces.java first
 */
import java.util.*;

class AAA {
	interface B {
		void f();
	}
	
	public class BPublicImp implements B {
		public void f() {
			System.out.println("BPublicImp::f()");
		}
	}

	class BPackageImp implements B {
		public void f() {
			System.out.println("BPackageImp::f()");
		}
	}

	private class BPrivateImp implements B {
		public void f() {
			System.out.println("BPrivateImp::f()");
		}
	}
	public B getB() {
		return new BPrivateImp();
	}
}

public class Temp {
	public static void main(String[] args) {
		AAA a = new AAA();
		AAA.B ab = a.getB();
		ab.f();
	}
}

/*
 If you have a package interface nested in a class, it does not matter what access specifier is given to
 its implementing classes. getB() can return an object of BPublicImp() or BPackageImp() or BPrivateImp().
*/

/*
 * Please read Temp1.java & Temp2.java next
 * and then Nesting.java.
 */
