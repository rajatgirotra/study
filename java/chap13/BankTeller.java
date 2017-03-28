/*
 * Please read ContainerMethodDifferences.java first
 * Read this carefully to see how generics can be used with Inner classes and anonymous inner classes
 */
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Random;

import generics.coffee.Generator;
class Customer {
	private static long counter = 0;
	private final long id = counter++;
	private Customer() {}
	public static Generator<Customer> generator() {
		return new Generator<Customer>() {
			public Customer next() {
				return new Customer();
			}
		};
	}
	public String toString() { return "Customer " + id; }
}

class Teller {
	private static long counter = 0;
	private final long id = counter++;
	private Teller() {}
	public static Generator<Teller> generator = 
				new Generator<Teller>() {
		public Teller next() {
			return new Teller();
		}
	};
	public String toString() { return "Teller " + id; }
}

public class BankTeller {
	public static void serve(Teller t, Customer c) {
		System.out.println(t + " serves " + c);
	}
	public static void main(String[] args) {
		Random rand = new Random();
		Queue<Customer> customerQueue = new LinkedList<Customer>();
		List<Teller> teller = new ArrayList<Teller>();
		Generators.makeList(teller, Teller.generator, 4);
		Generators.makeList(customerQueue, Customer.generator(), 15);
		//Note the difference in calling the generator in the above two lines.
		for(Customer c : customerQueue) {
			serve(teller.get(rand.nextInt(teller.size())), c);
		}
	}
}

/*
Please read Store.java next
*/