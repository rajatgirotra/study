/*
 * Please read p1.COne.java first
 */

package p2;

import p1.COne;

public class CTwo extends COne {
	 public void getIface() {
	        new COne.Inner();
	    }
}

/*
The reasoning is the same as in p2.ProtectedCtor.java
Please read Parcel4.java next
*/