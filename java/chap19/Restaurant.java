import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read NotifyVsNotifyAll.java next
 * We are creating a Chef and a WaitPerson object. The Chef will create a meal and will wait for the
 * WaitPerson to pick it. The WaitPerson will deliver it and then wait for the Chef to prepare the next
 * meal.
 */

class Meal {
	private int orderNo;
	Meal(int no) {
		this.orderNo = no;
	}
	public String toString() {
		return "Meal: " + orderNo;
	}
}

class WaitPerson implements Runnable {
	private Restaurant r;
	public WaitPerson(Restaurant r) {
		this.r = r;
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				//First wait if the Chef hasnt produced the meal
				synchronized(this) {
					while(r.meal == null) {
						wait();
					}
				}
				System.out.println("WaitPerson got " + r.meal);
				TimeUnit.MILLISECONDS.sleep(100);
				//Signal the chef that it has delivered the meal, so that Chef can prepare the next meal
				synchronized(r.chef) {
					r.meal = null;
					r.chef.notifyAll();
				}
			}
		}catch (InterruptedException e) {
			System.out.println("Exiting WaitPerson via interrupt");
		}
	}
}

class Chef implements Runnable {
	private Restaurant r;
	private int count = 0;
	Chef(Restaurant r) {
		this.r = r;
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				//First prepare a meal
				synchronized(this) {
					while(r.meal != null) {
						wait();
					}
				}
				if(++count == 10) {
					System.out.println("Out of Food... Closing!!");
					r.exec.shutdownNow();
				}
				System.out.print("Order Up!! ");
				//Prepare the meal now and signal the waitPerson
				synchronized(r.waitPerson) {
					Meal m = new Meal(count);
					r.meal = m;
					r.waitPerson.notifyAll();
				}
				//TimeUnit.MILLISECONDS.sleep(100);
				TimeUnit.MILLISECONDS.sleep(0);
			}
			System.out.println("Exiting Chef via Thread.interrupted");
		} catch(InterruptedException e) {
			System.out.println("Exiting Chef via Interrupt!!");
		}
	}
}

public class Restaurant {
	Meal meal;
	ExecutorService exec = Executors.newCachedThreadPool();
	Chef chef = new Chef(this); // Note this syntax; using this outside c'tor
	WaitPerson waitPerson = new WaitPerson(this);
	
	public Restaurant() {
		exec.execute(chef);
		exec.execute(waitPerson);
	}
	
	public static void main(String[] args) {
		new Restaurant();
	}
}

/*
Please read WaxOMatic2.java next
*/