/*
Please read RunTimeNullChecking.java first.

When you override a method, you can throw only the exceptions that have
been specified in the base-class version of the method. This is a useful
restriction, since it means that code that works with the base class will
automatically work with any object derived from the base class (a
fundamental OOP concept, of course), including exceptions. Feedback
This example demonstrates the kinds of restrictions imposed (at compile
time) for exceptions:

*/

import java.util.*;
class BaseballException extends Exception {}
class Foul extends BaseballException {}
class Strike extends BaseballException {}

abstract class Inning {
	Inning() throws BaseballException {}
	void event() throws BaseballException {
		// Doesn't actually have to throw anything
	}
	abstract void atBat() throws Strike, Foul;
	void walk() {} // Throws no checked exceptions
}
class StormException extends Exception {}
class RainedOut extends StormException {}
class PopFoul extends Foul {}
interface Storm {
	void event() throws RainedOut;
	void rainHard() throws RainedOut;
}
public class StormyInning extends Inning implements Storm {
	// OK to add new exceptions for constructors, but you
	// must deal with the base constructor exceptions:
	StormyInning() throws RainedOut, BaseballException {}
	StormyInning(String s) throws Foul, BaseballException {}

	// Regular methods must conform to base class:
	//void walk() throws PopFoul {} //Compile error
	// Interface CANNOT add exceptions to existing
	// methods from the base class:
	//public void event() throws RainedOut {}
	// If the method doesn't already exist in the
	// base class, the exception is OK:
	public void rainHard() throws RainedOut {}
	// You can choose to not throw any exceptions,
	// even if the base version does:
	public void event() {}
	// Overridden methods can throw inherited exceptions:
	void atBat() throws PopFoul {
		throw new PopFoul();
	}
	public static void main(String[] args) {
		try {
			StormyInning si = new StormyInning();
			si.atBat();
		} catch(PopFoul e) {
			System.err.println("Pop foul");
		} catch(RainedOut e) {
			System.err.println("Rained out");
		} catch(BaseballException e) {
			System.err.println("Generic baseball exception");
		}
		// Strike not thrown in derived version.
		try {
			// What happens if you upcast?
			Inning i = new StormyInning();
			i.atBat();
			// You must catch the exceptions from the
			// base-class version of the method:
		} catch(Strike e) {
			System.err.println("Strike");
		} catch(Foul e) {
			System.err.println("Foul");
		} catch(RainedOut e) {
			System.err.println("Rained out");
		} catch(BaseballException e) {
			System.err.println("Generic baseball exception");
		}
	}
}

/*
Please read NeverCaught.java next
*/