/*
 * Please read DynamicFields.java first
 */
import java.util.*;

class SimpleException extends Exception { }

class WiderException {
	public void f() throws SimpleException {
		throw new SimpleException();
	}
}
public class NarrowException extends WiderException {
	public void f() {
		System.out.println("NarrowException::f() - not throwing an exception");
	}
	
	public static void main(String[] args) throws SimpleException {
		NarrowException ne = new NarrowException();
		ne.f();
		
		WiderException we = new NarrowException();
		we.f();
	}
}

/*
Here you can see that if you’re dealing with exactly a NarrowException object,
the compiler forces you to catch only the exceptions that are specific to that class,
but if you upcast to the base type then the compiler (correctly) forces you to catch the
exceptions for the base type. All these constraints produce much more
robust exception-handling code.

It’s useful to realize that although exception specifications are enforced by
the compiler during inheritance, the exception specifications are not part
of the type of a method, which is comprised of only the method name and
argument types. Therefore, you cannot overload methods based on
exception specifications. In addition, just because an exception
specification exists in a base-class version of a method doesn’t mean that
it must exist in the derived-class version of the method. This is quite
different from inheritance rules, where a method in the base class must
also exist in the derived class. Put another way, the “exception
specification interface” for a particular method may narrow during
inheritance and overriding, but it may not widen—this is precisely the
opposite of the rule for the class interface during inheritance.

This is important: An exception specification can narrow down when going down from Base class to derived class,
but it may not widen.
The reason is that when you are working with a Base class reference, the compiler only knows about the base
class functions and the exceptions that they throw. It will never know any new exceptions thrown by derived 
class versions of those functions.

But the above is not true for c'tor. A derived class c'tor can add new exceptions, but it should
also handle the base class exceptions.

Please read RunTimeNullChecking.java next.
*/

