/*
MultiNestingAccess.java first
 

Because the inner class constructor must attach to a reference of the
enclosing class object, things are slightly complicated when you inherit
from an inner class. The problem is that the “secret” reference to the
enclosing class object must be initialized, and yet in the derived class
there’s no longer a default object to attach to. The answer is to use a
syntax provided to make the association explicit
 */
import java.util.*;

class WithInner {
	public WithInner() {
		System.out.println("WithInner c'tor");
	}

	class Inner {
		public Inner() {
			System.out.println("WithInner::Inner c'tor");
		}
	}
}
public class InheritInner extends WithInner.Inner {
	InheritInner(WithInner wi) {
		wi.super();
		System.out.println("InheritInner c'tor");
	}

	public static void main(String[] args) {
		WithInner wi = new WithInner();
		System.out.println("Separate");
		InheritInner ii = new InheritInner(wi);
	}
}

/*
You can see that InheritInner is extending only the inner class, not the
outer one. But when it comes time to create a constructor, the default one
is no good and you can’t just pass a reference to an enclosing object. In
addition, you must use the syntax.

enclosingClassReference.super();

inside the constructor. This provides the necessary reference and the
program will then compile.

AnonymousConstructor.java next
*/
