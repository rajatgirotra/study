/*
Sequence.java first

It doesn’t matter how deeply an inner class may be nested—it can
transparently access all of the members of all the classes it is nested
within, as seen here.
*/
import java.util.*;

class MNA {
	private void f() {}
	class A {
		private void g() {}
		public class B {
			void h() {
				g();
				f();
			}
		}
	}
}
public class MultiNestingAccess {
	public static void main(String[] args) {
		MNA mna = new MNA();
		MNA.A mna_a = mna.new A();
		MNA.A.B mna_a_b = mna_a.new B();
		mna_a_b.h();
	}
}

/*
InheritInner.java next
*/