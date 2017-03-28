import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import net.mindview.util.*;
/*
 * Please read DaemonThreadFactory.java first
 */
public class DaemonFromFactory implements Runnable {
	public void run() {
		try {
			while(true) { // this loop will terminate when the thread exists.
				TimeUnit.MILLISECONDS.sleep(50);
				System.out.println("Thread : " + Thread.currentThread());
			}
		} catch (InterruptedException e) {
			System.out.println("Thread: " + Thread.currentThread() + " interrupted");
		}		
	}
	
	public static void main(String[] args) {
		ExecutorService exec = Executors.newCachedThreadPool(new DaemonThreadFactory());
		for(int i = 0; i < 10; ++i) {
			exec.execute(new DaemonFromFactory());			
		}
		System.out.println("All daemons started.");
		try {
			TimeUnit.MILLISECONDS.sleep(500);
		} catch (InterruptedException e) {
			System.out.println("Interrupted in main");
		} // all daemons started.
		exec.shutdown();
	}
}
/*
 * Please read Daemons.java next
 */
