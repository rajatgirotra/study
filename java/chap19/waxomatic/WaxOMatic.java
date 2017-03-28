/*
 * Please read WaxOMatic.java
 * We have a car which has to be waxed and polished repeatedly.
 */

package waxomatic;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;


class Car {
	private volatile boolean waxOn = false;
	
	public synchronized void waxed() {
		waxOn = true;
		notifyAll();
	}
	public synchronized void buffed() {
		waxOn = false;
		notifyAll();
	}
	public synchronized void waitForBuffing() throws InterruptedException {
		//I.e wait for Buffing to be done.
		while(waxOn == true) {
			wait();
		}
	}
	public synchronized void waitForWaxing() throws InterruptedException {
		//wait for waxing to be done so that you can start polishing after that.
		while(waxOn == false) {
			wait();
		}
	}
}

class WaxOn implements Runnable {
	private Car car;
	WaxOn(Car c) {
		this.car = c;		
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				System.out.print("Wax On!!   ");
				TimeUnit.MICROSECONDS.sleep(200);
				car.waxed();
				car.waitForBuffing();
			}			
		}catch(InterruptedException e) {
			System.out.println("Exiting WaxOn via interrupt exception");
		}
		System.out.println("Exiting WaxOn task");
	}
}

class WaxOff implements Runnable {
	private Car car;
	WaxOff(Car c) {
		this.car = c;		
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				car.waitForWaxing();
				System.out.print("Wax Off!!   ");
				TimeUnit.MICROSECONDS.sleep(200);
				car.buffed();				
			}			
		}catch(InterruptedException e) {
			System.out.println("Exiting WaxOff via interrupt exception");
		}
		System.out.println("Exiting WaxOff task");
	}
}

public class WaxOMatic {
	public static void main(String[] args) throws InterruptedException {
		Car c = new Car();
		ExecutorService exec = Executors.newCachedThreadPool();
		exec.execute(new WaxOn(c));
		exec.execute(new WaxOff(c));
		TimeUnit.SECONDS.sleep(1);
		
		//shutdown all tasks.
		exec.shutdownNow();
	}
}

/*
The example emphasizes that you must surround a wait() with a while loop that checks the condition(s) of interest. This is 
important because:
	•	You may have multiple tasks waiting on the same lock for the same reason, and the first task that wakes up might
	 	change the situation (even if you don’t do this someone might inherit from your class and do it). If that is the 
	 	case, this task should be suspended again until its condition of interest changes. Please read CheckZero.java
	 	next to prove this to yourself.
	 	
	•	By the time this task awakens from its wait(), it’s possible that some other task will have changed things such 
		that this task is unable to perform or is uninterested in performing its operation at this time. Again, it should 
		be resuspended by calling wait() again.
		
	•	It’s also possible that tasks could be waiting on your object’s lock for different reasons (in which case you must 
		use notifyAll( )). In this case, you need to check whether you’ve been woken up for the right reason, and if not, 
		call wait() again.
		
	Thus, it’s essential that you check for your particular condition of interest, and go back into wait() if that condition 
	is not met. This is idiomatically written using a while.
	
Please read CheckZero.java next	
*/