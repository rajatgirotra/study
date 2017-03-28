import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

/*
 * Please read Must_Read_3.txt first
 * In order to terminate a blocked task, you can call Thread.interrupt(). this function sets the interrupt status of this task.
 * It throws an InterruptException if the thread was in a blocked state. When the exception is thrown the interrupt status
 * is automatically cleared; this means that inside the "catch" block, the interrupt status will always be false.
 * 
 * The interrupt status can also be cleared by a call to Thread.interrupted() function call. This call returns the interrupt status
 * and then clears the flag. So if you call this function twice in succession, the second call will always return false.
 * 
 * To call interrupt, you must have the Thread reference with you. But if you are using the Executor interface; then you
 * dont have that. To solve this, you can do the following:
 * 
 * 1] Call ExecutorService.shutdownNow() - this will call Thread.interrupt() for each thread that it started.
 * 
 * 2] Submit the task using ExecutorService.submit(Runnable r) & not using ExecutorService.execute(Runnable r).
 * This is because ExecutorService.submit(Runnable r) return a Future<?>, which you can use to call Future<?>.cancel(boolean)
 * to cancel the thread.  If the parameter passed to cancel() is true, then cancel() may call Thread.interrupt() to terminate the
 * specific task.
 */

class SleepBlocked implements Runnable {
	public void run() {
		try {
			TimeUnit.SECONDS.sleep(100);
		}catch(InterruptedException e) {
			System.out.println("SleepBlocked interrupted");
		}
		System.out.println("Exiting SleepBlocked interrupted");
	}
}

class IOBlocked implements Runnable {
	private InputStream in;
	public IOBlocked(InputStream in) {
		this.in = in;
	}
	public void run() {
		try {
			System.out.println("Waiting for read()");
			in.read();
		}catch(IOException e) {
			e.printStackTrace(System.out);
			if(Thread.currentThread().isInterrupted()) {
				System.out.println("Interrupted from blocked I/O, isInterrupted: " + Thread.currentThread().interrupted());
			}
			else {
				throw new RuntimeException(e);
			}
		}
		System.out.println("Exiting IOBlocked.run()");
	}
}

class SynchronizedBlocked implements Runnable {
	public synchronized void f() {
		while(true) {
			Thread.yield(); //never release the lock 
		}
	}
	public SynchronizedBlocked() {
		new Thread() {
			public void run() {
				f(); // Lock acquired by this thread.
			}
		}.start();
	}
	public void run() {
		System.out.println("Trying to call f()");
		f();
		System.out.println("Exiting SynchronizedBlocked.run()");
	}
}
public class Interrupting {
	private static ExecutorService exec = Executors.newCachedThreadPool();
	static void test(Runnable r) throws InterruptedException {
		Future<?> f = exec.submit(r);
		TimeUnit.MILLISECONDS.sleep(100);
		System.out.println("Interrupting " + r.getClass().getSimpleName());
		f.cancel(true);
		System.out.println("Interrupt sent to " + r.getClass().getSimpleName());
	}
	public static void main(String[] args) throws InterruptedException {
		//test(new SleepBlocked());
		test(new IOBlocked(System.in));
		//test(new SynchronizedBlocked());
		TimeUnit.SECONDS.sleep(3);
		System.out.println("Aborting with System.exit(0)");
		System.exit(0);
	}
}

/*
From the output you can notice that you are able to interrupt the sleep() call but you are not able to interrupt IO blocking
calls and synchronized blocking calls. This is also evident from the fact that you do not require an InterruptedException to
handle IO and synchronized blocking calls.

When you run this program, the main thread sleeps for 3 seconds, before waking up. In between this time, if you enter anything on 
the console, and hit <return>, you'll see that the IOBlocked thread runs further to completion, proving that it was not 
interrupted by the Thread.interrupt call.

It might be a concern that in I/O operation has the potential of locking up your multi-threaded program. A solution to this
problem is to close the underlying resource on which the task is blocked.

Please read CloseResource.java next

A very Important Word about exec.shutdown()
-------------------------------------------

exec.shutdown() will do the following:
1] Any tasks which were previously submitted will be executed.
2] Any new tasks will not be accepted.
3] Any blocked tasks will be unaffected.
*/