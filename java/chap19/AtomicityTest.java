import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/*
 * Please read AttemptLocking.java first
 * Here also we demonstrate the use of synchronized keyword.
 */
public class AtomicityTest implements Runnable {
	private int currentValue = 0;
	
	public int getValue() {
		return currentValue;
	}
	
	public synchronized void evenIncrement() {
		++currentValue;
		++currentValue;
	}
	
	public void run() {
		while(true) {
			evenIncrement();			
		}
	}
	
	public static void main(String[] args) {
		ExecutorService exec = Executors.newCachedThreadPool();
		AtomicityTest at = new AtomicityTest();
		exec.execute(at);
		while(true) {
			int val = at.getValue();
			if (val % 2 != 0) {
				System.out.println(val + " is not even..!!");
				System.exit(0);
			}
		}
	}
}

/*
You should also make getValue() synchronized to overcome the bug
Please read AtomicIntegerTest.java next
*/