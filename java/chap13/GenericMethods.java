/*
 * Please read IterableFibonacci.java first
 * Just like classes, class methods can also be parameterized. Methods can be parameterized irrespective of whether
 * the class has been parameterized or not. See a simple example below:
 * 
 * To write a generic method precede the return value of the method with the parameterized types as shown.
 * As a general rule you should write a generic method whenever u can. Also a static method of a class cannot access the
 * parameterized type of the class, so for it to use genericity, it must be a generic method.  
 */
public class GenericMethods {
	public static <T> void foo(T x) {
		System.out.println(x.getClass().getName());
	}
	
	public static void main(String[] args) {
		foo("");
		foo(1);
		foo(1.9);
		foo(1.9F);
		foo('c');
		foo(true);
	}
}

/*
 * Note that you get the sense that the function foo() has been infinitely overloaded. :) 
 * Also note that when you create a parameterized class, you need to explicitly specify the exact type when creating an
 * instance of that class. But with generic methods; this is not mandated. The compiler can infer the type automatically for 
 * you. This is called TYPE ARGUMENT INFERENCE.
 * 
 * Please read New.java next
 */