import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/*
 * Please read MultiLock.java first
 * You have already read that if you block on a synchronized method call, then that call is non-interruptible.
 * A solution to make it interruptible is to use the explicit Lock library as shown below; instead of using synchronized.
 */

class BlockedMutex {
	private Lock lock = new ReentrantLock();
	BlockedMutex() {
		//get the lock upfront. This will disable any synchronized method calls until
		//this lock is released.
		lock.lock();
	}
	public void f() {
		System.out.println("Waiting for f()");
		try {
			lock.lockInterruptibly();
		} catch (InterruptedException e) {
			System.out.println("Breaking out of the blocked call");			
		}		
	}
}

class BlockedMutex2 implements Runnable {
	private BlockedMutex bm = new BlockedMutex();
	public void run() {
		bm.f();
		System.out.println("After calling f()");
	}
}

public class Interrupting2 {
	public static void main(String[] args) throws Exception {
		Thread t = new Thread(new BlockedMutex2());
		t.start();
		
		TimeUnit.SECONDS.sleep(4);
		System.out.println("Issuing an interrupt request to the blocked task");
		t.interrupt();
	}
}

/*
Please read InterruptingIdiom.java next
*/