/*
 * Please read generics.coffee classes and Generator.java first.
 */

import java.util.Iterator;
import java.util.Random;

import generics.coffee.*; 

public class CoffeeGenerator implements Generator <Coffee>, Iterable<Coffee> {
	private static Random rand = new Random(47);
	int size;
	//one arg c'tor
	CoffeeGenerator(int sz) {
		size = sz;
	}
	public CoffeeGenerator() {
	}
	@SuppressWarnings("unchecked")
	private static Class[] types = new Class[] { Americano.class, Breve.class, Cappuccino.class, Latte.class, Mocha.class }; 
	public Coffee next()  {
		int n = rand.nextInt(types.length);
		try {
			return (Coffee)types[n].newInstance();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public class CoffeeIterator implements Iterator<Coffee> {
		int count = size;
		public boolean hasNext() {
			return count > 0;
		}

		public Coffee next() {
			count --;
			return CoffeeGenerator.this.next(); //--> See how to access the outer class Object corresponding to this inner class.
		}

		public void remove() {
			throw new UnsupportedOperationException();
		}
	}

	public Iterator<Coffee> iterator() {
		return new CoffeeIterator();
	}
	public static void main(String[] args) {
		CoffeeGenerator gen = new CoffeeGenerator();
		for(int i = 0; i < 5; i++)
			System.out.println(gen.next());
		for(Coffee c : new CoffeeGenerator(5))
			System.out.println(c);
	}
}
