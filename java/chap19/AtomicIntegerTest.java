import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;

/*
 * Please read AtomicityTest.java first.
 * JAVA SE 5 provides classes like AtomicInteger, AtomicLong, AtomicReference etc, 
 * that has functions which are atomic and cannot be interrupted.
 */
public class AtomicIntegerTest implements Runnable {
	private AtomicInteger ati = new AtomicInteger(0);
	public int getValue() {
		return ati.get(); //When get() is running and you call addAndGet(), that call will block.
	}
	
	public void evenIncrement() {
		ati.addAndGet(2);
	}
	
	public void run() {
		while(true) {
			evenIncrement();
		}
	}
	
	public static void main(String[] args) {
		ExecutorService exec = Executors.newCachedThreadPool();
		new Timer().schedule(new TimerTask() {
			public void run() {
				System.out.println("Aborting");
				System.exit(0);
			}
		}, 5000);
		
		AtomicIntegerTest at = new AtomicIntegerTest();
		exec.execute(at);
		while(true) {
			int val = at.getValue();
			if(val % 2 != 0) {
				System.out.println(val + " is not even");
				System.exit(0);
			}
		}
	}
}

/*
Please read AtomicEvenGenerator.java next
*/