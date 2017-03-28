/*
Parcel9.java first

When you create an inner class, an object
of that inner class has a link to the enclosing object that made it, and so it
can access the members of that enclosing object—without any special
qualifications. In addition, inner classes have access rights to all the
elements in the enclosing class.

the inner class can access methods and fields from the enclosing class as if it owned
them. This turns out to be very convenient, as you can see in the below
example. The inner class must keep a reference to the particular object of the enclosing class
that was responsible for creating it.

This is very different from the design of nested classes in C++, which is simply a namehiding
mechanism. There is no link to an enclosing object and no implied permissions in
C++.
*/

import java.util.*;

interface Selector {
	boolean end();
	Object current();
	void next();
}
public class Sequence {
	private int i = 0;
	private Object[] objects = null;
	public Sequence (int size) {
		objects = new Object[size];
	}
	public void add(Object x) {
		if(i < objects.length) {
			objects[i] = x;
			i++;
		}
	}
	
	public Selector getSelector() {
		return new Selector() {
			private int indx = 0;
			public boolean end() {
				return ( indx == objects.length);
			}
			
			public Object current() {
				return objects[indx];
			}
			
			public void next() {
				if( indx < objects.length) {
					indx++;				
				}
			}
			//static int p = 0;  an inner class cannot have static fields. Need to find out why??
			static final int p = 0; // but when declared final, it works OK. Need to find out why??	
		};
	}
	
	/*
	private class SSelector implements Selector {
		private int indx = 0;
		public boolean end() {
			return ( indx == objects.length);
		}
		
		public Object current() {
			return objects[indx];
		}
		
		public void next() {
			if( indx < objects.length) {
				indx++;				
			}
		}
		//static int p = 0;  an inner class cannot have static fields. Need to find out why??
		static final int p = 0; // but when declared final, it works OK. Need to find out why??	 
	}
	*/
	public static void main(String[] args) {
		Sequence s = new Sequence(10);
		Selector sel = s.getSelector();
		for(int i = 0; i < 10; ++i) {
			s.add(Integer.toString(i));
		}
		
		while(!sel.end()) {
			System.out.println(sel.current());
			sel.next();
		}			
	}
}

/*
MultiNestingAccess.java next
*/