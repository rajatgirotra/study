/*
 * Please read FactoryConstraint.java first.
 * As you saw in Erased.java, you cannot create an array of Generics inside generic code like this:
 * T[] array = new T[SIZE]; as the type information is not available.
 * What you can do instead is create an arrayList, and create add() & get() methods as shown below.
 */
import java.util.*;
public class ListOfGenerics<T> {
	private List<T> list = new ArrayList<T>();
	public void add(T item) {
		list.add(item);
	}
	public T get(int index) {
		return list.get(index);
	}
	
	public static void main(String[] args) {
		ListOfGenerics<Integer> intList = new ListOfGenerics<Integer>(); 
		//intList is your new array now. Use add() and get() methods to add or get.
		//this type of implementation also provides type-safety.
		intList.add(6); //autoboxing going on.
		System.out.println(intList.get(0));
	}
}
/*
please reas ArrayOfGenericReference.java next
*/