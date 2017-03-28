/*
there’s an important difference
between either form of instanceof (that is, instanceof or
isInstance( ), which produce equivalent results) and the direct
comparison of the Class objects. Here’s an example that demonstrates
the difference:
 */

// The difference between instanceof and class
class Base {}
class Derived extends Base {}

public class FamilyVsExactType {

	static void test(Object x) {
		System.out.println("Testing x of type " +

				x.getClass());
		System.out.println("x instanceof Base " +
				(x instanceof Base));
		System.out.println("x instanceof Derived " +
				(x instanceof Derived));
		System.out.println("Base.isInstance(x) " +
				Base.class.isInstance(x));
		System.out.println("Derived.isInstance(x) " +
				Derived.class.isInstance(x));
		System.out.println("x.getClass() == Base.class " +
				(x.getClass() == Base.class));
		System.out.println("x.getClass() == Derived.class " +
				(x.getClass() == Derived.class));
		System.out.println("x.getClass().equals(Base.class)) "+
				(x.getClass().equals(Base.class)));
		System.out.println(
				"x.getClass().equals(Derived.class)) " +
				(x.getClass().equals(Derived.class)));
	}
	public static void main(String[] args) {
		test(new Base());
		test(new Derived());
	}
}

/*
In
keeping with the concept of type, instanceof says “are you this class, or a
class derived from this class?” On the other hand, if you compare the
actual Class objects using ==, there is no concern with inheritance—it’s
either the exact type or it isn’t.
*/