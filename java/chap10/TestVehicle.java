import java.util.*;

class Vehicle {
	public String vehicleType() {
		return "Simple";
	}
}

class Car extends Vehicle {
	public String vehicleType() {
		return "Car";
	}
}

class Truck extends Vehicle {
	public String vehicleType() {
		return "Truck";
	}
}

public class TestVehicle {
	public static void main(String[] args) {
		Object o = new Vehicle();
		if(o instanceof Vehicle) 
			System.out.println("Object is an instanceof Vehicle");
		else
			System.out.println("Object is not an instanceof Vehicle");

		if(o instanceof Car) 
			System.out.println("Object is an instanceof Car");
		else
			System.out.println("Object is not an instanceof Car");

		Object o1 = new Car();
		if(o1 instanceof Car) 
			System.out.println("Object1 is an instanceof Car");
		else
			System.out.println("Object1 is not an instanceof Car");

		Object o2 = new Truck();
		if(o2 instanceof Car) 
			System.out.println("Truck is an instanceof Car");
		else
			System.out.println("Truck is not an instanceof Car");

		Class cls = Car.class;
		if(cls.isInstance(o2))
			System.out.println("Car is an instanceof Truck");
		else
			System.out.println("Car is not an instanceof Truck");
		
	}
}

