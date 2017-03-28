/*
 * Please read MutexEvenGenerator.java first * 
 */

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.*;
public class AttemptLocking {
	private ReentrantLock lock = new ReentrantLock();
	
	public void untimed() {
		boolean captured = lock.tryLock();
		try {
			System.out.println("untimed trylock: " + captured);
		}finally {
			if(captured) {
				System.out.println("untimed lock unlocked");
				lock.unlock();
			}
		}
	}
	
	public void timed() {
		boolean captured = false;
		try {
			captured = lock.tryLock(2, TimeUnit.SECONDS);
		}catch(InterruptedException e) {
			throw new RuntimeException(e);
		}
		try {
			System.out.println("timed lock: " + captured);
		}finally {
			if(captured) {
				System.out.println("timed lock unlocked");
				lock.unlock();
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		final AttemptLocking al = new AttemptLocking();
		al.untimed();
		al.timed();
		
		new Thread() {
			{
				setDaemon(true);
			}
			public void run() {
				al.lock.lock();
				System.out.println("acquired");
			}
		}.start();
		
		Thread.yield(); //this will enable to Thread created above to be run befor the following two statements.
		//try to cooment the above statement to see the difference.
		TimeUnit.SECONDS.sleep(1);
		
		al.untimed();
		al.timed();
				
	}
}

/*
Please read AtomicityTest.java next
*/