/*
 * InheritInner.java first
 */

import java.util.*;

abstract class Base {
	private int i;
	public Base(int i) {
		System.out.println("Base c'tor: i = " + i);
		this.i = i;
	}
	abstract void f();
	
	public int getI() {
		return i;
	}
}
public class AnonymousConstructor {
	public static Base getBase(final int i) {
		return new Base(i) {
			{
			//	super(i);
				System.out.println("Inner class initialization");
			}
			public void f() {
				System.out.println("AnonymousConstructor::f(), i = " + i);
			}
		};
	}
	public static void main(String[]  args) {
		Base base = getBase(47);
		base.f();
	}	
}

/* 

You can think of it this way.
When you say "new Base(i)", it means that whatever is in the argument list of the Base()
will be used as the argument list to the call to its base class c'tor

this seems to be the only way to call a base class c'tor. I tried using super() but got an error.
You can try that too.

BigEgg.java next
*/
