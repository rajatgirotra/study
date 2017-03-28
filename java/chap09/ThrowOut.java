/*
PLease read Rethrowing.java first.

Since Throwable is a base class of Exception, it’s
possible to get an object that’s a Throwable but not an Exception, so
the handler for Exception in main( ) might miss it. To make sure
everything is in order, the compiler forces an exception specification for
Throwable. For example, the exception in the following program is not
caught in main().
 */

import java.util.*;

public class ThrowOut {
	public static void main(String[] args) throws Throwable {
		try {
			throw new Throwable();
		}catch (Exception e) {
			System.err.println("Exception caught in main.");
		}
	}
}

/*
Please read ReThrowNew.java next
*/