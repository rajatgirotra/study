/*
Please read Must_Read_2.txt first
*/

class Vehicle {
	public String toString() {
		return getClass().getSimpleName();
	}
}

class Car extends Vehicle {}
class Bus extends Vehicle {}
class NotRelated {}

public class ExtendingGenerics<T extends Vehicle> {
	private T x;
	public ExtendingGenerics(T arg) {
		x = arg;
	}
	
	public T get() {
		return x;
	}
	
	public static void main(String[] args) {
		Vehicle v = new Vehicle();
		Bus b = new Bus();
		Car c = new Car();
		ExtendingGenerics<Vehicle> ev = new ExtendingGenerics<Vehicle>(c);
		System.out.println(ev.get());
		
		//ExtendingGenerics<NotRelated> ur = new ExtendingGenerics<NotRelated>(null);
	}
}
/*
Please read Must_Read_3.txt next
*/