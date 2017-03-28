/*
 Please read LostException.java first
There’s often some piece of code that you want to execute whether or not
an exception is thrown within a try block. You can use the finally keyword for it.
 */
import java.util.*;

class ThreeException extends Exception { }
public class FinallyWorks {
	
	private static int count = 0;
	public static void main(String[] args) {
		while (true) {
			try {
				if(count++ == 0) {
					throw new ThreeException();
				}
				System.out.println("No Exception");
			} catch(ThreeException e) {
				System.out.println("ThreeException caught");
			} finally {
				System.out.println("In finally clause");
				if(count == 2)
					break;
			}
		}//end of while.
	}
}

/*
This program also gives a hint for how you can deal with the fact that
exceptions in Java (like exceptions in C++) do not allow you to resume
back to where the exception was thrown, as discussed earlier. If you place
your try block in a loop, you can establish a condition that must be met
before you continue the program. You can also add a static counter or
some other device to allow the loop to try several different approaches
before giving up. This way you can build a greater level of robustness into
your programs.

Please read AlwaysFinally.java next
*/