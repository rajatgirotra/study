/*
 * Please read WaxOMatic.java first
 * What notifyAll() does is that it wakes-up the task and puts in a Runnable state. i.e the task can now start contending 
 * for the CPU. In our example here, both the tasks which called wait() become Runnable, but only one can be allowed to run.
 * The problem is that if the "checkValueEqualsZero()" tasks gets the CPU, it changes the value of variable back to -1, 
 * so the other task ("checkValueGreaterThanZero") should again start waiting. But this does not happen, as it is not in a 
 * while loop. So ideally, all calls to wait() should be inside a while loop.
 */

import java.util.concurrent.TimeUnit;


public class CheckZero {
	private volatile int value = -1;
	public synchronized void checkValueEqualsZero() throws InterruptedException {
		while(value != 0) {
			wait();
		}
		value = -1;
		System.out.println("checkValueEqualsZero proceeding on..!!");
	}
	
	public synchronized void checkValueGreaterThanZero() throws InterruptedException {
		if(value < 0) {
			wait();
		}
		value  = -1;
		System.out.println("checkValueGreaterThanZero moving on too..!!");
	}
	public synchronized void makeZero() {
		value = 0;
		notifyAll();
	}
	
	public static void main(String[] args) throws Exception {
		final CheckZero cz = new CheckZero();
		System.out.println("Calling CheckZero.checkValueEqualsZero()");
		new Thread() {
			public void run() {
				try {
					cz.checkValueEqualsZero();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}.start();
		
		TimeUnit.SECONDS.sleep(3);
		System.out.println("Calling CheckZero.checkValueGreaterThanZero()");
		new Thread() {
			public void run() {
				try {
					cz.checkValueGreaterThanZero();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}.start();
		
		TimeUnit.SECONDS.sleep(3);
		System.out.println("Calling CheckZero.makeZero()");
		cz.makeZero();		
	}
}

/*
Please read Exercise21.java next
On the other hand notify() only wakes up one task out of the many that are waiting(); and you cannot guarantee which one
will be woken up. So if you have many tasks all waiting on a different condition, and you call notify() you never know
whether the task that woke up was with that condition or not.

Using notify() instead of notifyAll() is mostly an optimization.
*/