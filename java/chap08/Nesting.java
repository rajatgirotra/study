/*
 * Please read Temp.java first
 */
class X {
	private interface Y {
		void f();
	}
	
	public class YPublic implements Y {
		public void f() {
			System.out.println("Ypublic::f()");
		}
	}
	
	private class YPrivate implements Y {
		public void f() {
			System.out.println("YPrivate::f()");
		}
	}
	
	class YPackage implements Y {
		public void f() {
			System.out.println("YPackage::f()");
		}
	}
	
	protected class YProtected implements Y {
		public void f() {
			System.out.println("YProtected::f()");
		}
	}
	public Y getY() {
		return new YPackage();
	}
	private Y yref;
	public void getYRef(Y y) {
		y.f();
	}
}
public class Nesting {
	
	public static void main(String[] args) {
		Nesting n = new Nesting();
		X x = new X();		
		x.getYRef(x.getY());	
	}
}

/*
Please read TestRandVals.java next
*/