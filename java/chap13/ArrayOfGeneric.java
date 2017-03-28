/*
 * Please read ArrayOfGenericReference.java first
 */
public class ArrayOfGeneric {
	static final int SIZE=100;
	static Generic<Integer>[] gia;
	
	public static void main(String[] args) {
		//Now since all arrays have the same structure (size of each array slot, and the array layout),
		//it might seem that we can create an array of Object[] and then cast it to Generic<Integer>. 
		//i.e.
	//	gia = (Generic<Integer>[])(new Object[SIZE]);	
		//The above causes a class Cast exception. This is because an array keeps track of its type, and the type is the
		//type at the time of creation of the array. So event though you cast it to a Generic<Integer>[] at compile time,
		//at run time it is still an Object and that causes problems. 
		
		//What you can do is create an array of the erased type (ie. Generic) & then cast that.
		gia = (Generic<Integer>[])new Generic[SIZE];
		System.out.println(gia.getClass());
		gia[0] = new Generic<Integer>();		
		//gia[1] = new Object(); // Compile-time error
		// Discovers type mismatch at compile time:
		// gia[2] = new Generic<Double>();
		
		
	}	
}

/*
Please read GenericArray.java next
*/