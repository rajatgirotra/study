import java.util.*;

class AAAA {
	public interface B {
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

public class Temp1 {
	public static void main(String[] args) {
		AAAA a = new AAAA();
		AAAA.B ab = a.getB();
		ab.f();
	}
}

/*
 If you have a public interface nested in a class, it does not matter what access specifier is given to
 its implementing classes. getB() can return an object of BPublicImp() or BPackageImp() or BPrivateImp().
*/
