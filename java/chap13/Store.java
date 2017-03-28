import generics.coffee.Generator;

import java.util.ArrayList;
import java.util.Random;

/*
 * Please read BankTeller.java first
 * Another program to understand the power of generics.
 * We create a model of a store, where the store has many aisles. Each aisle has many shelves
 * and each shelf has many products. Each product is identified by a unique id, has a description
 * and a price tag.
 */

class Product {
	private long id;
	private String desc;
	private double price;
	Product(long id, String desc, double price) {
		this.id = id;
		this.desc = desc;
		this.price = price;
		//System.out.println(toString());
	}
	public String toString() {
		return "id: " + id + " desc: " + desc + " price: $" + price;
	}
	
	public static Generator<Product> generator = new Generator<Product>() {
		private Random rand = new Random();
		public Product next() {
			return new Product(rand.nextInt(1000), "Test",
			Math.round(rand.nextDouble() * 500.0) + 0.99);
		}
	};
}

//each shelf has many products
class Shelf extends ArrayList<Product> {
	Shelf(int n_products) {
		Generators.makeList(this, Product.generator, n_products);
	}
}

//there are multiple shelves down each aisle.
class Aisle extends ArrayList<Shelf> {
	Aisle(int n_shelves, int n_products) {
		for(int i =0; i < n_shelves; ++i) {
			add(new Shelf(n_products));	
		}		
	}
}

class CheckoutStand { }
class Office { }

public class Store extends ArrayList<Aisle>{
	private ArrayList<CheckoutStand> list = new ArrayList<CheckoutStand>();
	private Office off = new Office();
	Store(int n_aisles, int n_shelves, int n_products) {
		for(int i = 0; i < n_aisles; ++i) {
			add(new Aisle(n_shelves, n_products));
		}
	}
	
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for(Aisle a : this) {
			for(Shelf s : a) {
				for(Product p : s) {
					sb.append(p);
					sb.append("\n");
				}
			}
		}
		return sb.toString();
	}
	
	public static void main(String[] args) {
		System.out.println(new Store(2,2,3));
	}
}

/*
Please read Must_Read_1.txt next
*/