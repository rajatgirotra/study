import java.util.*;

class PrivateOverride {
	private void f() {
		System.out.println("private f()");
	}

	public static void main(String[] args) {
		PrivateOverride po = new Derived();
		//The public interface of PrivateOverride does not contain the
		//member function f(). So this call will always resolve to the
		//private member function f() of PrivateOverride.
		po.f();
	}
}

class Derived extends PrivateOverride {
	public void f() {
		System.out.println("public f()");
	}
}

/*
Also compare this class to FinalOverridingIllusion.java in Chap06.
You'll notice that over there a similar call is throwing an error.
But here it is not the case.
The reason is that in that class the call to function f() is inside
another class, so the private function f() is not available. Over here
the call to function f() is inside its own class. So its available.
*/