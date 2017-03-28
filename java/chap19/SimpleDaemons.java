import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read SimplePriorities.java first
 * There are two types of Threads.
 * 1] Daemon threads - These are the ones which provide something like a service in the background for a long time.
 * 2] Non-Daemons - These are the regular threads that are created in the program. 
 * 
 *  A daemon thread can be created by call Thread.setDaemon(true) before the Thread.start() is called.
 *  If there are no non-daemon threads running, the program will terminate, killing the daemon threads in the process.
 *  If there is even one non-daemon thread still running, the program will not terminate.
 *  The example below created 10 dameon threads and displays them. *
 */
public class SimpleDaemons implements Runnable {
	public void run() {
		try {
			TimeUnit.MILLISECONDS.sleep(100);
			System.out.println(Thread.currentThread() +  ": " + this);			
		} catch(Exception e) {
			System.out.println(e);
		}
	}
	
	public static void main(String[] args) throws InterruptedException {
		Thread t = null;
		for(int i = 0; i < 9; ++i) {
			t = new Thread(new SimpleDaemons());
			t.setDaemon(true);
			t.start();
		}	
		System.out.println("In main..!!");
		TimeUnit.MILLISECONDS.sleep(100);
	}
}

/*
There’s nothing to keep the program from terminating once main() finishes its job, since there are nothing but daemon threads 
running. So that you can see the results of starting all the daemon threads, the main() thread is briefly put to sleep. 
Without this, you see only some of the results from the creation of the daemon threads.

If you set the sleep interval to anything less than 50 in main, no output is produced. This is because the main thread
terminates killing all the daemon threads in the process.

Also instead of creating the Threads explicitly using the Thread c'tor, we can make use of the ThreadFactory interface.
The ThreadFactory interface provides a "public Thread newThread(Runnable r)" interface. Using this you can create Threads
of your choice (i.e your own priority, daemon or not, etc etc.). We make use of ThreadFactory interface in the next example.

Please see DaemonThreadFactory.java next.
*/