/*
 * Please read TestRandomVals.java first
 */
import java.util.*;

public class TestBed {
	public TestBed() {
		System.out.println("Test bed c'tor");
	}
	
	@SuppressWarnings("unused")
	private static class Tester {
		public static void main(String[] args) {
			TestBed tb = new TestBed();
			tb.f();
		}
	}
	
	void f() {
		System.out.println("TestBed::f()");
	}
}


/* 
i did not understand this, TestBed should ideally have a main method
because it is a public class.

Answer:

Any class that can have a static method can have a public static void main(String[] args).

This includes:

top-level classes (whether public or not), e.g.

public class Foo {
    public static void main(String[] args) { 
        System.out.println("Hello"); 
    }
}
and inner static classes (whether public or not) (like your example).

It does not include:

anonymous classes
inner non-static classes

So both of these are illegal:

public class Foo {
    private Object bar = new Object() {
        public static void main(String[] args) {
            System.out.println("Hello");
        }
    };
}


public class Foo {
    private class Bar {
        public static void main(String[] args) {
            System.out.println("Hello");
        }
    };
}

Please read Parcel1.java next
*/
