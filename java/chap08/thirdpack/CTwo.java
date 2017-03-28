package thirdpack;

import intfpack.IOne;
import classpack.COne;

public class CTwo extends COne {
	public IOne getIOne() {
		IOne io = new Inner();
		
		Class<?> cls = COne.Inner.class;
		
		return io;		
	}
	
	public static void main(String[] args) {
		CTwo ctwo = new CTwo();
		ctwo.getIOne().f();
	}
}

/*
Now the JAVA Language Specification (JLS) says that you can access a protected inner class inside a
derived class. But here I am getting an error.

The problem is that the Inner class is accesssible. You can clearly see that the line:

Class<?> cls = COne.Inner.class;
does not print any error

It is the c'tor of the class Inner which is not accessible.
The error message is complaining about the constructor being protected,
not the class. But you haven't explicitly defined a constructor in the code you posted. In this case,
according to the JLS, the default constructor will be protected (the same as the class).

So if you define a public c'tor it should be fine.

Please read Base.java and p1.ProtectedCtor.java next
*/