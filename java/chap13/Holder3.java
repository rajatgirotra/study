/*
 * Please read BasicGeneratorDemo.java first
 * A holder class to hold automobile objects.
 * T is the type parameter.
 */

class Automobile {
	public String toString() {
		return "Automobile";
	}
	public void run() {		
	}
}
public class Holder3<T> {
	T a;
	Holder3(T a) {
		this.a = a;
	}
	public void set(T a) {
		this.a = a;
	}
	public T get() {
		return a;
	}
	
	public static void main(String[] args) {
		Holder3<Automobile> h = new Holder3<Automobile>(new Automobile());
		@SuppressWarnings("unused")
		Automobile a = h.get(); //No cast needed. The compiler evaluates it.
		//h.set("Not an automobile"); // this is an error
		//h.set(1); //this is an error too.
	}
}

/*
Please read Holder.java next
*/