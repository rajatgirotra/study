/*
 * Please read Holder3.java first.
 * Show that a holder that is specified to hold a base type can also hold derived types
 */

class Dog {
	public String toString() {
		return getClass().getSimpleName();
	}
}

class Mutt extends Dog {	
}

class Pug extends Dog {	
}


public class Holder<T> {
	T a;
	Holder(T a) {
		this.a = a;
	}
	Holder() {		
	}
	public void set(T a) {
		this.a = a;
	}
	public T get() {
		return a;
	}
	public boolean equals(Object obj) {
		return a.equals(obj);
	}
	public static void main(String[] args) {
		Holder<Dog> dogList = new Holder<Dog>(new Dog());
		System.out.println(dogList.get());
		
		dogList = new Holder<Dog>(new Pug());
		System.out.println(dogList.get());
		
		dogList = new Holder<Dog>(new Mutt());
		System.out.println(dogList.get());		
	}	
}

/*
Please read TwoTuple.java next
*/