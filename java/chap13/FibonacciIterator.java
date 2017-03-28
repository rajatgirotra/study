import java.util.Iterator;

/*
 * Please read Fibonacci.java first
 * Here we are creating an Iterator for Fibonacci so that it can be used in a foreach loop.
 */
public class FibonacciIterator extends Fibonacci implements Iterable<Integer> {
	private int count;
	FibonacciIterator(int size) {
		count = size;
	}
	public Iterator<Integer> iterator() {
		return new Iterator<Integer>() {
			public Integer next() {
				count --;
				return FibonacciIterator.this.next();
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
		for(Integer i : new FibonacciIterator(18)) {
			System.out.print(i + " ");
		}
	}
}

/*
Please read IterableFibonacci.java next
*/