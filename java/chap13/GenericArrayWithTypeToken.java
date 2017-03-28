import java.lang.reflect.Array;

/*
 * Please read GenericArray2.java first
 * If you still want to keep T[] inside your class, then you should pass the Class object of the parameter type
 * T in the c'tor and use the Array.newInstance(type, size) function instead.
 */
public class GenericArrayWithTypeToken<T> {
	private T[] array;

	@SuppressWarnings("unchecked")
	GenericArrayWithTypeToken(Class<T> type, int size) {
		array = (T[])Array.newInstance(type, size);
	}

	public void put(int index, T item) {
		array[index] = item;
	}

	public T get(int index) {
		return array[index];
	}

	public T[] rep() {
		return (T[])array;
	}

	public static void main(String[] args) {
		GenericArrayWithTypeToken<Integer> gai = new GenericArrayWithTypeToken<Integer>(Integer.class, 10);
		// This now works:
		Integer[] ia = gai.rep();
	}
}

/*
 Unfortunately, if you look at the source code in the Java SE5 standard libraries, you’ll see there are casts 
 from Object arrays to parameterized types everywhere. For example, here’s the copy-ArrayList-from-Collection 
 constructor, after cleaning up and simplifying:
 
public ArrayList(Collection c) {
	size = c.size();
	elementData = (E[])new Object[size];
	c.toArray(elementData);
}

If you look through ArrayList.java, you’ll find plenty of these casts. And what happens when we compile it?
Note: ArrayList.java uses unchecked or unsafe operations.
Note: Recompile with -Xlint:unchecked for details.

In his weblog,3 Neal Gafter (one of the lead developers for Java SE5) points out that he was lazy when rewriting 
the Java libraries, and that we should not do what he did. Neal also points out that he could not fix some of 
the Java library code without breaking the existing interface. So even if certain idioms appear in the Java library 
sources, that’s not necessarily the right way to do it. When you look at library code, you cannot assume that it’s 
an example that you should follow in your own code.
*/

/*
 * Please read Must_Read_6.txt next
 */
