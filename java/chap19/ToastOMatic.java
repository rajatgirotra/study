import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;

/*
 * Please read TestBlockingQueues.java first
 * We have to create a Toast, then apply butter on it, then jam, and finally eat it.
 * We have to create 4 threads, one each for creating a toast, applying butter, applying jam, and finally eating
 * We'll demonstrate how the use of BlockingQueue drastically reduce the complexity of code.
 */

//Toast class

class Toast {
	public enum Status { DRY, BUTTERED, JAMMED };
	private int id;
	private Status status = Status.DRY;
	public Toast(int idn) {
		id = idn;
	}
	public Status getStatus() {
		return status;
	}
	public void butter() {
		status = Status.BUTTERED;
	}
	public void jam() {
		status = Status.JAMMED;
	}
	public int getID() {
		return id;
	}
	public String toString() {
		return "Toast " + id + "  Status: " + status;
	}
}

//BlockingQueue class to simplify code
class ToastQueue extends LinkedBlockingQueue<Toast> {}

//class to create a Toast object
class Toaster implements Runnable {
	ToastQueue dryQueue;
	int counter = 0;
	public Toaster(ToastQueue dry) {
		dryQueue = dry;
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				Toast t = new Toast(counter++);
				dryQueue.put(t);
				TimeUnit.MILLISECONDS.sleep(200);
			}
		}catch (InterruptedException e) {
			System.out.println("Exiting toaster via interrupt");
		}
		System.out.println("Finishing Toaster job");
	}
}

//Butter class to butter the toast
class Butterer implements Runnable {
	ToastQueue dryQueue, butteredQueue;	
	public Butterer(ToastQueue dry, ToastQueue buttered) {
		dryQueue = dry;
		butteredQueue = buttered;
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				Toast t = dryQueue.take();
				//Butter the toast now.
				t.butter();
				System.out.println(t);
				//Put the buttered toast onto the butteredQueue.
				butteredQueue.put(t);
			}
		}catch(InterruptedException e) {
			System.out.println("Exiting butterer via interrupt");
		}
		System.out.println("Finished buttering job");
	}	
}


//Jam class to apply Jam to the toast
class Jammer implements Runnable {
	ToastQueue butteredQueue, finishedQueue;
	
	public Jammer(ToastQueue butteredQueue, ToastQueue finishedQueue) {
		this.butteredQueue  = butteredQueue;
		this.finishedQueue = finishedQueue;
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				Toast t = butteredQueue.take();
				//Jam the toast now.
				t.jam();
				System.out.println(t);
				//Put the buttered toast onto the butteredQueue.
				finishedQueue.put(t);
			}
		}catch(InterruptedException e) {
			System.out.println("Exiting jammer via interrupt");
		}
		System.out.println("Finished jammer job");
	}	
}

//class Eater to consume the toast
class Eater implements Runnable {
	ToastQueue finishedQueue;
	private int count = 0;
	Eater(ToastQueue finalQueue) {
		finishedQueue = finalQueue;
	}
	
	public void run() {
		try {
			while(!Thread.interrupted()) {
				Toast t = finishedQueue.take();
				if(t.getID() != count++ || t.getStatus() != Toast.Status.JAMMED) {
					System.out.println("Error: " + t);
					System.exit(-1);
				}
				else {
					System.out.println("Chomp " + t);
				}
			}
		}catch (InterruptedException e) {
			System.out.println("Exiting eater via interrupt");
		}
		System.out.println("Finished eating job");
	}
}

public class ToastOMatic {
	public static void main(String[] args) throws Exception {
		ToastQueue dryQueue       = new ToastQueue();
		ToastQueue butterQueue    = new ToastQueue();
		ToastQueue finishedQueue  = new ToastQueue();
		ExecutorService exec = Executors.newCachedThreadPool();
		exec.execute(new Toaster(dryQueue));
		exec.execute(new Butterer(dryQueue, butterQueue));
		exec.execute(new Jammer(butterQueue, finishedQueue));
		exec.execute(new Eater(finishedQueue));
		
		//Let it run for some time.
		TimeUnit.SECONDS.sleep(5);
		
		//Send an interrupt to shutdown processes.
		exec.shutdownNow();		
	}
}

/*
Please read PipedIO.java next
*/