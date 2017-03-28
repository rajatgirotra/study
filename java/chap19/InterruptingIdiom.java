import java.util.concurrent.TimeUnit;

/*
 * Please read Interrupting2.java first
 * When we call, Thread.interrupt(), the thread raises an InterruptedException only if it was blocked. If is was not blocked,
 * and was doing some computational work, then Thread.interrupt() will only set the interrupt flag of the thread.
 * We can read this flag using Thread.interrupted(). And as you already know, Thread.interrupted() clears the interrupt flag
 * too.
 * 
 *  Any Runnable method() must provide support to handle both blocked and unblocked possibilities when the interrupt status is
 *  set.  
 */

class NeedsCleanup {
	private final int id;
	public NeedsCleanup(int id) {
		this.id = id;
		System.out.println("NeedsCleanup " + id);
	}
	public void cleanup() {
		System.out.println("Cleaning up " + id);
	}
}

class Blocked3 implements Runnable {
	private volatile double d = 0.0;
	public void run() {
		try {
			while(!Thread.interrupted()) {

				//point 1
				NeedsCleanup n1 = new NeedsCleanup(1);
				try {
					System.out.println("Sleeping");
					//Go to sleep for some time.
					TimeUnit.MILLISECONDS.sleep(50);

					//point 2
					NeedsCleanup n2 = new NeedsCleanup(2);
					
					//System.out.println("Sleeping b4 calculating");     //--->>> A
					//TimeUnit.SECONDS.sleep(1);     //--->>> A
					
					try {
						System.out.println("Calculating");
						// A time-consuming, non-blocking operation:
						for(int i = 1; i < 25000000; i++)
							d = d + (Math.PI + Math.E) / d;
						System.out.println("Finished time-consuming operation");
					} finally {
						n2.cleanup();
					}
				} finally {
					n1.cleanup();
				}
			}
			System.out.println("Exiting via while() test");
		} catch(InterruptedException e) {
			System.out.println("Exiting via InterruptedException");
		}
	}
}
public class InterruptingIdiom {
	public static void main(String[] args) throws Exception {
		if(args.length != 1) {
			System.out.println("usage: java InterruptingIdiom delay-in-mS");
			System.exit(1);
		}
		Thread t = new Thread(new Blocked3());
		t.start();
		TimeUnit.MILLISECONDS.sleep(new Integer(args[0]));
		t.interrupt();
	}
}

/*
Note that all NeedsCleanup resources created in Blocked3.run() must be immediately followed by try-finally clauses to 
guarantee that the cleanup( ) method is always called. This is beacuse if there is a blocking call between the allocation
of resource and the start of the try block, then the program might get interrupted at that blocking call, without calling
the finally clause to cleanup the allocated resource. 
You can uncomment lines marked as A and check for yourself.

This run takes a command line argument which is the time in millisecond after which the run() thread is interrupted.
Accordingly you'll get different output depending on whether the thread gets interrupted while it was blocked or while it
was performing useful operation.

Please read Must_Read_4.txt next.
*/