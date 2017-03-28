/*
 * Please read Base.java first.
 */
package p1;

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
Here the c'tor of Base is protected. But it does not cause any problems in creating of object of 
type Base or Derv in the same package, as you can see in ProtectedCtor.

Please read p2.ProtectedCtor next
*/