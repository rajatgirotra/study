/*
 * Please read AtomicIntegerTest.java first
 * This is MutexEvenGenerator.java re-written using AtomicInteger class.
 */

import java.util.concurrent.atomic.AtomicInteger;
public class AtomicEvenGenerator extends IntGenerator {
	private AtomicInteger currentValue = new AtomicInteger(0);
		
	public int next() {
		return currentValue.addAndGet(2);		
	}
	
	public static void main(String[] args) {
		EvenChecker.test(new AtomicEvenGenerator());
	}
}

/*
Please read CriticalSection.java next
*/
