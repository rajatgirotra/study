/*
Please read ThrowOut.java first
*/
import java.util.*;

class OneException extends Exception {
	public OneException(String s) {
		super(s);
	}
}

class TwoException extends Exception {
	public TwoException(String s) {
		super(s);
	}
}

class ReThrowNew {
	public static void f() throws OneException {
		System.err.println("throwing OneException from f()");
		throw new OneException("one exception from f()");		
	}
	public static void main(String[] args) throws TwoException {
		try {
			f();
		}catch (OneException e) {
			e.printStackTrace();
			throw new TwoException("from main()");
		}
	}	
}

/*
Please read DynamicFields.java next
*/