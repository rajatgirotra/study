//import A.DImp2;

/*
Please read HorrorShow.java first
*/

/* A class can have a nested interface */
/* A class can have a nested class */


class AA {
	interface BB { 
		void f();
	}
	public class BBImp implements BB {
		public void f() {}
	}
	@SuppressWarnings("unused")
	private class BBImp2 implements BB {
		public void f() {}
	}
	public interface CC {
		void f();
	}
	class CCImp implements CC {
		public void f() {}
	}
	@SuppressWarnings("unused")
	private class CCImp2 implements CC {
		public void f() {}
	}
	private interface DD {
		void f();
	}
	@SuppressWarnings("unused")
	private class DDImp implements DD {
		public void f() {}
	}
	public class DDImp2 implements DD {
		public void f() { System.out.println("DImp2::f()"); }
	}

	// Returning a reference to a private interface..??
	public DD getD() { return new DDImp2(); }
	private DD dRef;
	public void receiveD(DD d) {
		dRef = d;
		dRef.f();
	}
}
interface EE {
	interface GG {
		void f();
	}
	// Redundant "public":
	public interface HH {
		void f();
	}
	void g();
	// Cannot be private within an interface:
	//! private interface I {}
}
public class NestingInterfaces {
	public class BBImp implements AA.BB {
		public void f() {}
	}
	class CCImp implements AA.CC {
		public void f() {}
	}
	// Cannot implement a private interface except
	// within that interface's defining class:
	//class DDImp implements AA.DD {
	// public void f() {}
	// }
	class EEImp implements EE {
		public void g() {}
	}
	class EGImp implements EE.GG {
		public void f() {}
	}
	class EEImp2 implements EE {
		public void g() {}
		class EG implements EE.GG {
			public void f() {}
		}
	}
	public static void main(String[] args) {
		AA a = new AA();
		// Can't access AA.DD:
		//! AA.DD ad = a.getD();
		// Doesn't return anything but AA.DD:
		// AA.DDImp2 di2 = a.getD();
		// What about this??
		AA.DDImp2 di2 = (AA.DDImp2)a.getD();
		di2.f();
		// Cannot access a member of the interface:
		//a.getD().f();
		// Only another AA can do anything with getD():
		//this is the workaround
		AA a2 = new AA();
		a2.receiveD(a.getD());
	}
} ///:~

/*
Interface E shows that interfaces can be nested within each other.
However, the rules about interfaces—in particular, that all interface
elements must be public—are strictly enforced here, so an interface
nested within another interface is automatically public and cannot be
made private.
NestingInterfaces shows the various ways that nested interfaces can be
implemented. In particular, notice that when you implement an interface,
you are not required to implement any interfaces nested within. Also,
private interfaces cannot be implemented outside of their defining
classes
*/

/*
Please read Temp.java, Temp1.java and Temp2.java next
*/