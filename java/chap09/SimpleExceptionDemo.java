/*
 * Please read must_read_1.txt first
 */
import java.util.*;

public class SimpleExceptionDemo extends Exception {
	void f() throws SimpleExceptionDemo {
		System.out.println("SimpleExceptionDemo::f() throwing exception..!!");
		throw new SimpleExceptionDemo();
	}
	
	public static void main(String[] args) {
		SimpleExceptionDemo sed = new SimpleExceptionDemo();
		try {
			sed.f();
		}catch(SimpleExceptionDemo se) {
			System.err.println("Caught it..!!");
		}
	}
}

/*
Please read ExtraFeatures.java next
*/