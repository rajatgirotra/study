/*
 * Please read ClosedResource.java first
 * This class is just a reiteration of Interrupting.java & ClosedResource.java
 */

import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class IOBlock implements Runnable {
	InputStream in;
	
	public IOBlock(InputStream in) {
		this.in = in;
	}
	public void run() {
		try {
			System.out.println("About to read from input stream");
			in.read();
		}catch(IOException e) {	
			
			System.out.println("IOException Caught");
			if(Thread.currentThread().isInterrupted()) {
				System.out.println("SleepBlock interrupted, interrupted: true" );	
			}
			else {
				throw new RuntimeException(e);
			}			
		}
	}
}

class SleepBlock implements Runnable {
	public void run() {
		try {
			//Sleep for 10 seconds.
			TimeUnit.SECONDS.sleep(10);			
		}catch(InterruptedException e) {		
			System.out.println("SleepBlock interrupted, interrupted: " + Thread.currentThread().interrupted());									
		}
	}
}

class SynchronizeBlock implements Runnable {
	public synchronized void f() {
		while(true) {
			Thread.yield(); //Never release the lock.
		}
	}
	public SynchronizeBlock() {
		new Thread() {
			public void run() {
				f();
			}
		}.start();
	}
	
	public void run() {
		System.out.println("Trying to call f()");
		f();
		System.out.println("Exiting SynchronizedBlock.run()");
	}
}

//This class is used to demonstrate how you can use locks in place of synchronized methods
//which have the advantage that these can be interrupted.
class InterruptingSyncBlock {
	private Lock lock = new ReentrantLock();
	
	public InterruptingSyncBlock() {
		//Take the block in the c'tor itself, so that no sync method can be called on this method.
		lock.lock();
	}
	
	public void f() {
		//Instead of using synchronized, use locks.
		System.out.println("Waiting in f() to get the lock.");
		try {
			lock.lockInterruptibly();
		}catch(InterruptedException e) {
			System.out.println("Interrupted: Unable to acquire lock in f().");
		}
	}
}

class DemonstrateSyncLock implements Runnable {
	InterruptingSyncBlock isb = new InterruptingSyncBlock();
	
	public void run() {
		isb.f();
	}
}
public class ThreadInterrupting {
	public static void main(String[] args) throws Exception {
		
		//First, SleepBlock
		ExecutorService exec = Executors.newCachedThreadPool();
		exec.execute(new SleepBlock());
		
		//Wait for 200 milli and then cancel the thread.
		TimeUnit.MILLISECONDS.sleep(200); //This will allow SleepBlock thread to be scheduled.
		exec.shutdownNow(); //--> shutDownNow send a Thread.interrupt to the SleepBlock task,
							//    so that should get interrupted.
		
		/* You can also start the thread using exec.submit() and cancel it using Future.cancel.
		 * But remember, you'll still  need to call exec.shutDown() to shutdowm gracefully.
		 */
		exec = Executors.newCachedThreadPool();
		Future<?> f = exec.submit(new SleepBlock());
		//Again, wait as before.
		TimeUnit.MILLISECONDS.sleep(200);
		//now cancel.
		f.cancel(true); //-> true argument ensures waiting tasks are also canceled.
		//Shutdown now.
		exec.shutdown();
		
		//------------------------------------------------------------------------------------------//
		//Run with one of the 2 blocks enabled at any one time.
/*		
		//Next IOBlock		
		exec = Executors.newCachedThreadPool();
		exec.execute(new IOBlock(System.in));
		//Wait for 2000 milli and then cancel the thread.		
		TimeUnit.MILLISECONDS.sleep(2000);
		exec.shutdownNow(); //-> You'll notice that nothing happens here. The IOBlock which is blocking on
							//an I/O operation, does not get interrupted.
		
*/		
/*		
		//Same behavior with Future.cancel.
		exec = Executors.newCachedThreadPool();
		f = exec.submit(new IOBlock(System.in));
		TimeUnit.MILLISECONDS.sleep(2000);
		exec.shutdown();		
		f.cancel(true); //IOBlock not interrupted here as well.
		
*/		//------------------------------------------------------------------------------------------//
		
		//Run with one of the 2 blocks enabled at any one time.
/*		
		//Now to protect a IO blocking operation from halting your application, the workaround is to
		//close the stream itself. i.e. to destroy the underlying resource itself. So here we just make 
		//a call to System.in.close() and achieve what we want.
		exec = Executors.newCachedThreadPool();
		exec.execute(new IOBlock(System.in));
		//Wait for 100  milli and then cancel the thread.		
		TimeUnit.MILLISECONDS.sleep(100);
		//call shutdownNow to interrupt the IOBlock task.
		exec.shutdownNow();
		//Now close the stream.
		System.in.close();
		//The moment you enter something on the console as input and press enter, an IOException is raised that
		//the Stream is closed. Also since you had called shutDownNow() which calls Thread.interrupt(), 
		//Thread.isInterrupted() is also true.		 
		 */
		
		/*
		//Using Future.cancel() to achieve same behavior
		exec = Executors.newCachedThreadPool();
		f = exec.submit(new IOBlock(System.in));
		//Wait for 100  milli and then cancel the thread.		
		TimeUnit.MILLISECONDS.sleep(100);
		//call shutdown to disable any tasks from being submitted.
		exec.shutdown();
		//cancel the IOBlock task now.
		f.cancel(true);//true means that a blocked task will be interrupted.
		//f.canel(false); //false means that a blocked task will not be interrupted.
		//Now close the stream.
		System.in.close();
		//The moment you enter something on the console as input and press enter, an IOException is raised that
		//the Stream is closed. Also since you had called shutDownNow() which calls Thread.interrupt(), 
		//Thread.isInterrupted() is also true. 		 
		 */
		//------------------------------------------------------------------------------------------//
			
		//Now synchronized block.
		//You can see that even after waiting 3 seconds after sending the interrupt, the synchronized block does
		//not get interrupted.
		exec = Executors.newCachedThreadPool();
		exec.execute(new SynchronizeBlock());
		TimeUnit.MILLISECONDS.sleep(1000);
		//Now interrupt the SynchronizedBlock.run() task
		exec.shutdownNow();
		TimeUnit.SECONDS.sleep(3);		
		//------------------------------------------------------------------------------------------//
		
		//Now, we'll see how we can use Lock instead of synchronized keyword and get interruptible synchronized 
		//blocks.
		exec = Executors.newCachedThreadPool();
		exec.execute(new DemonstrateSyncLock());
		TimeUnit.SECONDS.sleep(5);
		//Now send an interrupt
		System.out.println("Issuing an interrupt request to the blocked task");
		exec.shutdownNow(); //--> this will result in interruptedException.
	}
}

/*
Please read NIOInterruption.java next 
*/