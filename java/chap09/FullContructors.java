/*
Please read ExceptionMethods.java first
*/
import java.util.*;

class MyException extends Exception {
	public MyException() { }
	public MyException(String message) {
		super(message);
	}
}

public class FullContructors {
	public static void f() throws MyException {
		System.err.println("Throwing exception from f()");
		throw new MyException();
	}
	
	public static void g() throws MyException {
		System.err.println("Throwing exception from g()");
		throw new MyException("thrown from g()");
	}
	
	public static void main(String[] args) {
		try {
			System.err.println("Calling f() now");			
			f();
		}catch (MyException e) {
			e.printStackTrace();
		}
		try {
			System.err.println("Calling g() now");
			g();			
		}catch (MyException e) {
			e.printStackTrace();
		}		
	}
}

/*
In the handlers, one of the Throwable (from which Exception is
inherited) methods is called: printStackTrace( ). This produces
information about the sequence of methods that were called to get to the
point where the exception happened. By default, the information goes to
the standard error stream, but overloaded versions allow you to send the
results to any other stream as well.
*/

/*
Please read Must_Read_2.txt next
*/