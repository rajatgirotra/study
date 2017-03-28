/*
 * Please read Must_Read_2.txt first
 */
import java.util.*;

public class Rethrowing {
	public static void f() throws Throwable {
		System.err.println("Throwing an exception from Rethrowing::f()");
		throw new Exception("I am an exception string");
	}
	
	public static void g() throws Throwable {
		try {
			f();
		}catch (Exception e) {
			System.err.println("StackTrace(): ");
			e.printStackTrace();
			//throw e; //in this case the stack trace does not get modified. So what is printed before this is again printed same to same in catch block in g().
			throw e.fillInStackTrace(); // when you call fillInStackTrace(), the existing backtrace information is deleted and new stack frame starts building up from here.
		}
	}
	
	public static void main(String[] args) throws Throwable{
		try {
			g();
		}catch (Exception e) {
			System.err.println("Stacktrace: ");
			e.printStackTrace();
		}
	}
}

/*
If you simply rethrow the current exception, the information that you
print about that exception in printStackTrace( ) will pertain to the
exception’s origin, not the place where you rethrow it. If you want to
install new stack trace information, you can do so by calling
fillInStackTrace( ),

So whenever you are rethrowing an exception, consider using fillInStackTrace().
*/

/*
Please read ThrowOut.java next
*/