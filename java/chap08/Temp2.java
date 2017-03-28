import java.util.*;

class A {
	private interface B {
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
		return new BPackageImp();
	}
}

public class Temp2 {
	public static void main(String[] args) {
		A a = new A();
		//A.B ab = a.getB();
		A.BPublicImp ab = (A.BPublicImp)a.getB();
		ab.f();
	}
}

/*
 If you have a private interface nested in a class, you must downcast to a class which implements that interface.
 See how it is done when a.getB() is called. Remember, when you are downcasting you are running the risk of getting
 a ClassCastException as shown.
*/
