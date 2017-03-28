/*
 * Please read Wildcards.java first
 */

/*
One situation in particular requires the use of <?> rather than a raw type. If you pass a raw type to a method that 
uses <?>, it’s possible for the compiler to infer the actual type parameter, so that the method can turn around and 
call another method that uses the exact type. The following example demonstrates the technique, which is called capture 
conversion because the unspecified wildcard type is captured and converted to an exact type.
 */
public class CaptureConversion {
	public static <T> void f1(Holder<T> holder) {
		T t = holder.get();
		System.out.println(t.getClass().getSimpleName());
	}
	
	public static void f2(Holder<?> holder) {
		f1(holder);
	}
	
	public static void main(String[] args) {
		Holder hInt = new Holder<Integer>(1);
		f2(hInt);
		
		Holder hObj = new Holder();
		hObj.set(new Object());
		f2(hObj);
		
		Holder<?> hDouble = new Holder<Double>(1.0);
		f2(hDouble);		
	}
}
