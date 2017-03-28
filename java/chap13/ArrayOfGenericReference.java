/*
 * Please read ListOfGenerics.java first
 * Sometimes you might want to create an array of Generic types. This is possible as shown below.
 */

class Generic<T> { }

public class ArrayOfGenericReference {
	static Generic<Integer>[] gia;
	// you have actually created an array of Generic<Integer> references. i.e. each gia[] will point to an object
	//of Generic<Integer> class.
}
/*
please read ArrayOfGeneric.java next
*/