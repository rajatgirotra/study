import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read CheckZero.java first
 * Create two Runnables, one with a run( ) that starts and calls wait( ). The second class should capture the reference of 
 * the first Runnable object. Its run( ) should call notifyAll( ) for the first task after some number of seconds have 
 * passed so that the first task can display a message. Test your classes using an Executor.
 */

class Run1 implements Runnable {
	public synchronized void displayMessage() throws InterruptedException {
		wait();
		System.out.println("Wait Over.. Message: What do i do now??");
	}
	public void run() {
		try {
			this.displayMessage();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}

class Run2 implements Runnable {
	private Runnable run;
	Run2(Runnable r) {
		this.run = r;
	}
	public void run() {
		synchronized(run) {
			try {
				System.out.println("Sleeping for 1 seconds");
				TimeUnit.SECONDS.sleep(1);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("Notifying Everybody");
			run.notifyAll();
		}
	}
}
public class Exercise21 {
	public static void main(String[] args) {
		ExecutorService exec = Executors.newCachedThreadPool();
		Run1 r1 = new Run1();
		exec.execute(r1);
		exec.execute(new Run2(r1));
		exec.shutdown();
	}
}

/*
Please read Must_Read_5.txt next
*/