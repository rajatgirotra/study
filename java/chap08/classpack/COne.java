/*
 * Please read intfpack.IOne.java first
 */
package classpack;

import intfpack.*;

public class COne {
	protected class Inner implements IOne {
		//public Inner() {}
		public void f() {
			System.out.println("Inner::f()");
		}
	}
}
