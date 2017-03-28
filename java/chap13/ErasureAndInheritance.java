/*
 * Please read Must_Read_4.txt first.
 */

class GenericBase<T> {
	private T  obj;
	T get() {
		return obj;
	}
	void set(T obj) {
		this.obj = obj;
	}
}

 
//class Derived1 extends GenericBase<T> {}
//must add type parameter to derived class declaration.
// Otherwise when u say GenericBase<String> gen = new Derived1(), the compiler wont know the base class c'tor to run.

class Derived1<T> extends GenericBase<T> {} 
class Derived2 extends GenericBase { } 
//class Derived3 extends GenericBase<?> {} // a Base class cannot specify a wildcard as a parameter type

public class ErasureAndInheritance {
	//@SuppressWarnings("unchecked")
	public static void main(String[] args) {
	Derived2 d2 = new Derived2();
	Object obj = d2.get();
	d2.set(obj); // Warning here!
	}
}

/*
Please read ArrayMaker.java next
*/