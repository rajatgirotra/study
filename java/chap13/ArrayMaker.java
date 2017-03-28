import java.lang.reflect.Array;
import java.util.Arrays;

/*
 * Please read ErasureAndInheritance.java first
 */
public class ArrayMaker<T> {
	private Class<T> type;
	
	public ArrayMaker(Class<T> type) {
		this.type = type;
		System.out.println(type.getName());
	}
	//@SuppressWarnings("unchecked")
	public T[] create(int size) {
		return (T[])(Array.newInstance(type, size));
	}
	
	public static void main(String[] args) {
		ArrayMaker<String> am = new ArrayMaker<String> (String.class);
		String[] strArray = am.create(9);
		System.out.println(Arrays.toString(strArray));		
	}
}

/*
Even though kind is stored as Class<T>, erasure means that it is actually just being stored as a Class, with no 
parameter. So, when you do something with it, as in creating an array, Array.newInstance( ) doesn’t actually have the
type information that’s implied in kind; so it cannot produce the specific result, which must therefore be cast, 
which produces a warning that you cannot satisfy.

Please read Erased.java next
*/