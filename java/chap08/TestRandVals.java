/*
 * Please read Nesting.java  first
 */

/*
Fields defined in interfaces are automatically static and final. These
cannot be “blank finals,” but they can be initialized with non-constant
expressions. For example:
*/

import java.util.*;
import c08.RandVals;
public class TestRandVals {
	public static void main(String[] args) {
		System.out.println(RandVals.i);
		System.out.println(RandVals.l);
		System.out.println(RandVals.f);
		System.out.println(RandVals.d);		
		System.out.println();
		System.out.println(RandVals.i);
		System.out.println(RandVals.l);
		System.out.println(RandVals.f);
		System.out.println(RandVals.d);
	}
}

/*
The fields, of course, are not part of the interface but instead are stored in
the static storage area for that interface.

An interface can't have behavior or state because it is intended to specify only an interaction contract,
no implementation details.
 
1)No behavior is enforced by not allowing method/constructor bodies or static/instance initializing blocks.
2)No state is enforced by only allowing constants.

Please read TestRandomVals.java next
*/