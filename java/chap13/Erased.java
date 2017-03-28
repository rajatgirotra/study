/*
 * Please read ArrayMaker.java first
 * Using generics, there are certain operations that cannot be done at runtime.
 * Basically any operation that requires knowledge of the exact type at run time wont work.
 */
public class Erased<T> {
	private static final int SIZE = 100;
	public static void f(Object arg) {
		if(arg instanceof T) {
			T var = new T(); //Cant create a simple object this way
			T[] array = new T[SIZE]; //cant create an array of generics this way.
			T[] array2 = (T)new Object[SIZE];
		}
	}
}


/* 
You can see the errors above & the reasons for it.
To overcome these, you should mostly pass a Class object for your type, so that you
can use it in most of the expressions.

Please read ClassTypeCapture.java first.
*/
