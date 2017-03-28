import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.TimeUnit;

/*
 * Please read WaxOMatic2.java first
 * JAVA provides an interface called BlockingQueue. It is a Queue in which a take() operation waits
 * until the queue is non-empty, and a put() operation waits until the queue has capacity to insert more.
 * There are several implementations of BlockingQueue that can be used to synchronize tasks without
 * using wait() and notify() calls. This program demonstrates that.
 * 
 * What we do here is basically create a thread in main() which will pull out LiftOff elements from the
 * queue and call the run() function. The main thread on the other hand puts in LiftOff objects.
 * You'll see that there is no external synchronization mechanism required as all that is handled
 * implicitly by the BlockingQueue.
 */

class LiftOffRunner implements Runnable {
	private BlockingQueue<LiftOff> rockets;
	LiftOffRunner(BlockingQueue<LiftOff> queue) {
		rockets = queue;
	}
	public void add(LiftOff obj) {
		try {
			rockets.put(obj);
		} catch (InterruptedException e) {
			System.out.println("LiftOffRunner.add() interrupted");
		}
	}
	
	public void run() {
		try {
			while(!Thread.interrupted()) {
				//Take a LiftOff object and call its run() member function.
				LiftOff rocket = rockets.take();
				rocket.run();				
			}
		} catch (InterruptedException e) {
			System.out.println("LiftOffRunner.run() interrupted");
		}
		System.out.println("Exiting LiftOffRunner.run() ");
	}
}
public class TestBlockingQueues {
	public static void getKey() {
		try {
			new BufferedReader(new InputStreamReader(System.in)).readLine();
		} catch (IOException e ) {
			throw new RuntimeException(e);
		}
	}
	public static void getKey(String message) {
		System.out.println(message);
		getKey();
	}
	
	public static void testBlockingQueue(String msg, BlockingQueue<LiftOff> queue) {
		System.out.println(msg);
		LiftOffRunner runner = new LiftOffRunner(queue);
		Thread t = new Thread(runner);
		t.start();
		
		for(int i = 0; i < 5; ++i) {
			runner.add(new LiftOff(5));			
		}
		getKey("Press ‘Enter’ (" + msg + ")");
		t.interrupt();
		System.out.println("Finished " + msg + " test");
	}
	
	public static void main(String[] args) throws InterruptedException {
		//testBlockingQueue("LinkedBlockingQueue", new LinkedBlockingQueue<LiftOff>()); //infinite capacity
		System.out.println("");
		System.out.println("");
		
	//	testBlockingQueue("ArrayBlockingQueue", new ArrayBlockingQueue<LiftOff>(3)); //finite capacity
		System.out.println("");
		System.out.println("");
		
		testBlockingQueue("SynchronousQueue", new SynchronousQueue<LiftOff>()); //fixed capacity of one.		
	}
}

/*
Please read ToastOMatic.java next.
*/