/*
 * Please read Base.java first.
 */
package p2;

import p1.Base;

class Derv extends Base {
	public void foo() {
		Base base = new Derv();
		Base base2 = new Base();
	}
}
public class ProtectedCtor {
	public static void main(String[] args) {
		Base base = new Base();
		Base base2 = new Derv();
	}
}

/*
Here the c'tor of Base is protected. And it causes problems in creating of object of 
type Base as it is in a different package, as you can see in ProtectedCtor.

But the most important part: Notice that in creation of the Derv object, the Base class c'tor will be called
and that is not causing an issue. So a protected c'tor has the following limitations.

1) it limits the creation of Base to the other classes in package p1. That means that all classes in package p1 only
   will be able to create an object of Base.
   
2) it allows inheritors to call that constructor as part of their construction - Any body inheriting from Base
will be able to call the protected c'tor during its creation irrespective of the package in which the base class
is defined. That is why the Derv object creation line is not causing any error.

 Please read p1.COne.java next
*/