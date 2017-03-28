/*
 * Please read EvenGenerator.java first
 * JAVA SE5 also provides an explicit Locks library to simulate the synchronized keyword.
 * The advantage of using this is that if your synchronized method throws an exception, then you have no chance
 * to maintain your system in a proper state, but while using explicit locks, you can use a try-catch block to maintain
 * your system in a consistent state. Also, with Locks you can try and fail to get a lock, or try to get a timed lock.
 */

import java.util.concurrent.locks.*;
public class MutexEvenGenerator extends IntGenerator {
	private int currentValue = 0;
	private Lock lock = new ReentrantLock();
	
	public int next() {
		lock.lock();
		try {
			++currentValue;
			Thread.yield();
			++currentValue;
			return currentValue; //Even though there is a return statement here, the finally block will
								// still be executed.
		}finally {
			lock.unlock();
		}
	}
	
	public static void main(String[] args) {
		EvenChecker.test(new MutexEvenGenerator());
	}
}

/*
When you are using Lock objects, it is important to internalize the idiom shown here: Right after the call to lock(), 
you must place a try-finally statement with unlock() in the finally clause—this is the only way to guarantee that 
the lock is always released. Note that the return statement must occur inside the try clause to ensure that the 
unlock( ) doesn’t happen too early and expose the data to a second task.

Please read AttemptLocking.java next
*/