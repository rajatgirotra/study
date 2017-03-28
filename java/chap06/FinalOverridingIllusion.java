/*
final and private

Any private methods in a class are implicitly final. Because you cant
access a private method, you cant override it. You can add the final
specifier to a private method but it doesnt give that method any extra
meaning.

This issue can cause confusion, because if you try to override a private
method (which is implicitly final) it seems to work, and the compiler
doesnt give an error message:
*/

import java.util.*;

class WithFinals {
	private final void f() {
		System.out.println("WithFinals::f()");
	}

	private void g() {
		System.out.println("WithFinals::g()");
	}
}

class OverridingPrivate extends WithFinals {
	private final void f() {
		System.out.println("OverridingPrivate::f()");
	}

	private void g() {
		System.out.println("OverridingPrivate::g()");
	}
}

class OverridingPrivate2 extends OverridingPrivate {
	public final void f() {
		System.out.println("OverridingPrivate2::f()");
	}

	public void g() {
		System.out.println("OverridingPrivate2::g()");
	}
}

public class FinalOverridingIllusion {
	public static void main(String[] args) {
		OverridingPrivate2 op2 = new OverridingPrivate2();
		op2.f();
		op2.g();

		OverridingPrivate op = op2;
		//op.f();
		//op.g();

		WithFinals wf = op2;
		//wf.f();
		//wf.g();
	}
}

/*
Overriding can only occur if something is part of the base-class
interface. That is, you must be able to upcast an object to its base type and
call the same method (the point of this will become clear in the next
chapter). If a method is private, it isnt part of the base-class interface. It
is just some code thats hidden away inside the class, and it just happens
to have that name, but if you create a public, protected or packageaccess
method with the same name in the derived class, theres no
connection to the method that might happen to have that name in the
base class. You havent overridden the method, youve just created a new
method. Since a private method is unreachable and effectively invisible,
it doesnt factor into anything except for the code organization of the class
for which it was defined.
*/

