/*
 * Please read ExtraFeatures.java first.
 */
/* Some of the methods derived from Throwable */

import java.util.*;

public class ExceptionMethods {
	public static void main(String[] args) {
		try {
			throw new Exception("I am an exception string");		
		}catch (Exception e) {
			System.err.println("Caught exception");
			System.err.println("e.getMessage(): " + e.getMessage());
			System.err.println("e.getLocalisedMessage(): " + e.getLocalizedMessage());
			System.err.println("toString(): " + e);
			System.err.println("e.printStackTrace(): ");
			e.printStackTrace();
		}		
	}
}

/*
Please read FullConstructors.java next
*/