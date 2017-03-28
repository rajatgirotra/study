/*
 * Please read Restaurant.java first
 * In WaxOMatic.java, we are using a synchronized block and wait() and notifyAll() idiom.
 * But if use explicit locking instead of synchronized, we can use the Condition Object
 * and await() signalAll() objects.
 */

package waxomatic2;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Car {
	Lock lock = new ReentrantLock();
	Condition cond = lock.newCondition();
	public volatile boolean waxed = false;
	public void waxed() {
		try {
			lock.lock();
			waxed = true;
			cond.signalAll();
		} finally {
			lock.unlock();
		}
	}
	
	public void buffed() {
		try {
			lock.lock();
			waxed = false;
			cond.signalAll();
		} finally {
			lock.unlock();
		}
	}
	
	public void waitForWaxing() throws InterruptedException {
		//i.e. wait for Waxing to be done.
		try {
			lock.lock();
			while(waxed == false)
				cond.await();
		} finally {
			lock.unlock();
		}
	}
	
	public void waitForBuffing() throws InterruptedException {
		//i.e. wait for polishing to be done.
		try {
			lock.lock();
			while(waxed == true)
				cond.await();
		} finally {
			lock.unlock();
		}
	}
}

class WaxOn implements Runnable {
	private Car car;
	WaxOn(Car c) {
		car = c;
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				System.out.println("Wax ON..!!");
				TimeUnit.MILLISECONDS.sleep(200);
				car.waxed();
				car.waitForBuffing();
			}
		} catch(InterruptedException e) {
			System.out.println("Wax ON exiting via Interrupt");
		}
		System.out.println("Ending WaxOn Task...!!");
	}
}

class WaxOff implements Runnable {
	private Car car;
	WaxOff(Car c) {
		car = c;
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				car.waitForWaxing();
				System.out.println("Wax OFF..!!");
				TimeUnit.MILLISECONDS.sleep(200);
				car.buffed();				
			}
		} catch(InterruptedException e) {
			System.out.println("Wax OFF exiting via Interrupt");
		}
		System.out.println("Ending WaxOff Task...!!");
	}
}
public class WaxOMatic2 {
	public static void main(String[] args) throws InterruptedException {
		Car c = new Car();
		ExecutorService exec = Executors.newCachedThreadPool();
		exec.execute(new WaxOn(c));
		exec.execute(new WaxOff(c));
		TimeUnit.SECONDS.sleep(2);
		exec.shutdownNow();
	}
}

/*
Please read TestBlockingQueues.java next
*/