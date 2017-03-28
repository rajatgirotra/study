/*

Please read NarrowException.java first.

The first example in this chapter was
if(t == null)
throw new NullPointerException();

It can be a bit horrifying to think that you must check for null on every
reference that is passed into a method (since you can’t know if the caller
has passed you a valid reference). Fortunately, you don’t—this is part of
the standard run-time checking that Java performs for you, and if any call
is made to a null reference, Java will automatically throw a
NullPointerException. So the above bit of code is always superfluous.

*/

import java.util.*;

public class RuntimeNullChecking {
	private String id;
	RuntimeNullChecking(String id) {
		this.id = id;
		System.out.println("C'tor received string starting with: " + this.id.charAt(0));
	}
	
	public String toString() {
		return id;
	}
	
	public static void main(String[] args) {
		RuntimeNullChecking rtn = new RuntimeNullChecking(null);
		System.out.println(rtn);
	}
}

/*
Please read StormyInning.java next
*/