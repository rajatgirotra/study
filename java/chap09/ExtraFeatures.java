/*
 * Please read SimpleExceptionDemo.java first.
 */
import java.util.*;

class MyException2 extends Exception {
	private int i;
	MyException2() {}
	MyException2(String message) {
		super(message);
		this.i = -980232;
	}
	
	MyException2(String message, int val) {
		super(message);
		this.i  = val;
	}
	
	public int val() {
		return i;
	}
	
	public String getMessage() {
		return "Details: " + super.getMessage();
	}
}
public class ExtraFeatures {
	public static void f() throws MyException2 {
		throw new MyException2("I am from f() with", 47);
	}
	
	public static void main(String[] args) {
		try {
			f();
		}catch (MyException2 e) {
			System.err.println("Message " + e.getMessage() + " value: " + e.val());
		}
	}	
}

/*
A field i has been added, along with a method that reads that value and an
additional constructor that sets it. In addition,
Throwable.getMessage( ) has been overridden to produce a more
interesting detail message. getMessage( ) is something like toString( )
for exception classes.
*/

/*
Please read ExceptionMethods.java next. 
*/