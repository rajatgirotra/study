import java.util.*;

class Useful {
	void f() {
		System.out.println("Useful.f()");
	}
	void g() {
		System.out.println("Useful.g()");
	}
}

class MoreUseful extends Useful {
	void f() {
		System.out.println("MoreUseful.f()");
	}
	void g() {
		System.out.println("MoreUseful.g()");
	}
	void u() {
		System.out.println("MoreUseful.u()");
	}
}

public class RTTI {
	public static void main(String[] args) {
		Useful[] x = {
			new Useful(),
			new MoreUseful()
			};

		x[0].f();
		x[1].g();
		//x[0].u(); // Compile time error
		((MoreUseful)x[1]).u();
		//((MoreUseful)x[0]).u(); // run time exception thrown - ClassCastException
	}
}



