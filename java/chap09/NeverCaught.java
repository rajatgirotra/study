/*
Please read StormyInning.java first.

For class RunTimeException and all of its subclasses the compiler
does not enforce you to provide an exception specification.

What happens when you don’t catch such exceptions? Since the compiler
doesn’t enforce exception specifications for these, it’s quite plausible that
a RuntimeException could percolate all the way out to your main( )
method without being caught. To see what happens in this case, try the
following example:
 */

import java.util.*;
public class NeverCaught {
	public static void f() {
		throw new RuntimeException("from f()");		
	}
	
	public static void g() {
		f();
	}
	
	public static void main(String[] args) {
		g();
	}
}

/*
You can already see that a RuntimeException (or anything inherited
from it) is a special case, since the compiler doesn’t require an exception
specification for these types.

So the answer is: If a RuntimeException gets all the way out to
main( ) without being caught, printStackTrace( ) is called for that
exception as the program exits.

Keep in mind that you can only ignore exceptions of type
RuntimeException (and subclasses) in your coding, since all other
handling is carefully enforced by the compiler. The reasoning is that a
RuntimeException represents a programming error:

Please read LostException.java next
*/