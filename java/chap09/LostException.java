/*
Please read NeverCaught.java first.

Unfortunately, there’s a flaw in Java’s exception implementation.
Although exceptions are an indication of a crisis in your program and
should never be ignored, it’s possible for an exception to simply be lost.
This happens with a particular configuration using a finally clause:
 */

import java.util.*;

class VeryImportantException extends Exception {
	public String toString() {
		return "A very important exception";
	}
}

class TrivialException extends Exception {
	public String toString () {
		return "A trivial exception";
	}
}
public class LostException {
	void f() throws VeryImportantException {
		throw new VeryImportantException();
	}
	
	void dispose() throws TrivialException {
		throw new TrivialException();
	}
	
	public static void main(String[] args) throws Exception {
		LostException le = new LostException();
		try {			
			le.f();
		}finally {
			le.dispose();
		}
	}
}

/*
You can see that there’s no evidence of the VeryImportantException,
which is simply replaced by the TrivialException in the finally
clause. This is a rather serious pitfall, since it means that an exception can
be completely lost, and in a far more subtle and difficult-to-detect fashion
than the example above. In contrast, C++ treats the situation in which a
second exception is thrown before the first one is handled as a dire
programming error. Perhaps a future version of Java will repair this
problem.

Please read FinallyWorks.java next.
*/
