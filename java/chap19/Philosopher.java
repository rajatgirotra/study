import java.util.concurrent.TimeUnit;

/*
 * Please read Chopstick.java first
 */
public class Philosopher implements Runnable {
	//Left & right chopsticks
	private Chopstick left;
	private Chopstick right;
	
	//PonderFactor - time for which each philosopher will eat or think
	private int ponderFactor = 0;
	
	//each philosophers unique id
	private int id;
	
	public Philosopher(Chopstick r, Chopstick l, int idn, int ponder) {
		right = r;
		left = l;
		id = idn;
		ponderFactor = ponder;
	}
	public String toString() {
		return "Philosopher: " + id;
	}
	public void pause() throws InterruptedException {
		if(ponderFactor != 0) {
			TimeUnit.MILLISECONDS.sleep(ponderFactor);
		}
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				System.out.println(this + " thinking..!!");
				//Think
				pause();
				
				//Take the right & left chopstick
				System.out.println(this + " " + "grabbing right");
				right.take();
				System.out.println(this + " " + "grabbing left");
				left.take();
				
				//Eat
				System.out.println(this + " eating..!!");
				pause();
				
				//Drop the chopsticks to go back in thinking mode
				right.drop();
				left.drop();
			}
			System.out.println(this + " exiting via Thread.interrupted");
		}catch (InterruptedException e) {
			System.out.println(this + " exiting via interrupt");
		}
	}
}

/*
Please read DeadlockingDiningPhilosophers.java next
*/