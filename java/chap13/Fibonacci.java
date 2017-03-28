import generics.coffee.Generator;

/*
 * Please read CoffeeGenerator.java first
 */
public class Fibonacci implements Generator<Integer> {
	private int count = 0;
	public Integer next() {
		return fib(count++);
	}
	private Integer fib(int n) {
		if(n < 2)
			return 1;
		else
			return (fib(n-2) + fib(n-1));
	}
	
	public static void main(String[] args) {
		Fibonacci fi = new Fibonacci();
		for(int i = 0; i < 18; ++i) {
			System.out.print(fi.next() + " ");
		}
	}
}

/*
 *  The important thing to note here is that you can use Integer with int seamlessly, thanks to the autoboxing &
 *  autounboxing feature of JAVA.
 *  
 *  Please read FibonacciIterator.java next
 */