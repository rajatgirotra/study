import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read Must_read_5.txt first
 * notifyAll() will only wake up those threads that are also waiting on the same lock. It will not just wake up
 * all the threads in your application.
 */

class Blocker {
	public synchronized void waitingCall() {
		try {
			while(!Thread.interrupted()) {
				wait();
				System.out.println(Thread.currentThread());
			}	
		} catch(InterruptedException e) {
			System.out.println("Exiting via interrupt");
		}
	}
	public synchronized void prod() {
		notify();
	}
	public synchronized void prodAll() {
		notifyAll();
	}
}

class Task implements Runnable {
	public static Blocker blocker = new Blocker();
	public void run() {
		blocker.waitingCall();
	}
}

class Task2 implements Runnable {
	public static Blocker blocker = new Blocker();
	public void run() {
		blocker.waitingCall();		
	}
}

public class NotifyVsNotifyAll {
	public static void main(String[] args) throws Exception {
		ExecutorService exec = Executors.newCachedThreadPool();
		for(int i = 0; i < 5; ++i)
			exec.execute(new Task());
		exec.execute(new Task2());
		
		Timer timer = new Timer();
		timer.scheduleAtFixedRate(new TimerTask() {
			private boolean notifyAll = false;
			public void run() {
				if(notifyAll) {
					Task.blocker.prodAll();
					notifyAll = false;
				}
				else {
					Task.blocker.prod();
					notifyAll = true;
				}
			}
		}, 400, 1000); //Run every 1000 milliseconds.
		
		TimeUnit.SECONDS.sleep(2);
		timer.cancel(); //Cancel all subsequent tasks, but don't interfere with any task already running.
		System.out.println("Timer Cancelled");
		
		TimeUnit.MILLISECONDS.sleep(500);
		System.out.print("Task2.blocker.prodAll(): ");
		Task2.blocker.prodAll();
		TimeUnit.MILLISECONDS.sleep(500);
		
		System.out.println("\nShutting down");
		
		exec.shutdownNow();
	}	
}

/*
Please read Restaurant.java next
*/