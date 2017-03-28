/*
Please read FinallyWorks.java first

Even in cases in which the exception is not caught in the current set of
catch clauses, finally will be executed before the exception handling
mechanism continues its search for a handler at the next higher level:
 */

//: c09:AlwaysFinally.java
// Finally is always executed.
import java.util.*;

class FourException extends Exception {}
public class AlwaysFinally {
	public static void main(String[] args) {
		System.err.println("Entering first try block");
		try {
			System.err.println("Entering second try block");
			try {
				throw new FourException();
			}catch(FourException e) {
				System.err.println(
				"Caught FourException in 1st try block");
			}
			finally {
				System.err.println("finally in 2nd try block");
			}
		}  finally {
			System.err.println("finally in 1st try block");
		}
	}
} ///:~

/*
The finally statement will also be executed in situations in which break
and continue statements are involved. Note that, along with the labeled
break and labeled continue, finally eliminates the need for a goto
statement in Java.

Last program in this folder
*/