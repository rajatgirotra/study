import java.util.Iterator;

/*
 * Please read FibonacciIterator.java first
 * Here we are creating an Iterator for Fibonacci using composition instead of extending Fibonacci class.
 */
public class IterableFibonacci implements Iterable<Integer> {
	private int count;
	private Fibonacci fib = new Fibonacci();
	IterableFibonacci(int size) {
		count = size;
	}
	public Iterator<Integer> iterator() {
		return new Iterator<Integer>() {
			public Integer next() {
				count --;
				return fib.next();
			}
			public boolean hasNext() {
				return count > 0;
			}
			public void remove() {
				throw new UnsupportedOperationException();
			}
		};
	}
	public static void main(String[] args) {
		for(Integer i : new IterableFibonacci(18)) {
			System.out.print(i + " ");
		}
	}
}

/*
Please read GenericMethods.java next
*/