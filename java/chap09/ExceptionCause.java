/*
 * Please go through DynamicFields.java initial comments and then return here. 
 * The default implementation of inbuilt exception classes is:
 * 
 * public String getMessage() {
 *   if(causeObject exists)
 *      return causeObject.toString()
 *   else if(string was passed in c'tor)
 * 	 	return <the string which was passed to the c'tor when creating this object.
 *   else
 *      return "";
 * }
 * 
 * public String toString() {
 * 	return "Name of the class" + ": " + getMessage();
 * }
 * 
 * public void printStackTrace() {
 * 		System.err.println(this); -->> i.e. call toString();
 * 		System.err.println("<the actual stack trace>");
 * 		if(cause) { --> i.e. if a cause object exists
 * 			System.out.println("Cause by: ");
 * 			cause.printStackTrace();
 * 		}
 * }
 * 
 * Basically the cause object is nothing but a Throwable wrapped inside another Throwable.
 * When you call printStackTrace() it checks if there is a valid cause reference, if yes 
 * it call printStackTrace() for that cause.
 * 
 * For the fundamental exception classes, JAVA provides a c'tor to set the cause object
 * as we use here in "throw new RuntimeException(ec)" below.
 * For all other classes, JAVA provides an initCause() function.
 */

import java.util.*;
public class ExceptionCause extends Exception {
	public static void f() throws ExceptionCause {
		System.err.println("Throwing ExceptionCause");
		ExceptionCause ec = new ExceptionCause("I am an Exception Cause");
		ec.initCause(new NullPointerException("t==null"));
		throw ec;
	}
	
	/*
	public String toString() {
		return "Exception Details: ";
	}
	*/
	public ExceptionCause(String msg) {
		super(msg);
	}
	public static void main(String[] args) {
		try {
			f();
		}catch(ExceptionCause ec) {			
			throw new RuntimeException(ec);
		}
	}
}

/*
Now go back and read dynamicFields.java 
*/