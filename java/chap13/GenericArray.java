/*
 * Please read ArrayOfGeneric first.java first
 * This example is similar to ArrayOfGeneric, albeit a bit more sophisticated.
 */
public class GenericArray<T> {
	private T[] array;
	
	@SuppressWarnings("unchecked")	
	public GenericArray(int size) {
		array = (T[])new Object[size];
	}
	
	public void add(int index, T item) {
		array[index] = item;
	}
	
	public T get(int index) {
		return array[index];
	}
	
	public T[] rep() {
		return array;
	}
	
	public static void main(String[] args) {
		GenericArray<Integer> gai = new GenericArray<Integer>(10);
		Integer[] intArray = gai.rep();
		//The above produces a class cast exception as the underlying array type is Object.
		
		Object[] objArray = gai.rep(); //This is OK as the underlying type is also Object.
	}
}

/*
Please read GenericArray2.java next
*/