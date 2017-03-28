import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read CountDownLatchDemo.java first
 * A CyclicBarrier is another threading aid in JAVA 5 and later. It is used when you want to run many threads in parallel
 * and want all of them to stop at a point, which we call as the Barrier point. When all threads have reached the barrier
 * point, the CyclicBarrier runs another thread to check/change the state of the system. 
 * We will write a HorseRace program in which we have multiple horses running in a race. Each running horse is represented
 * by a thread; and each horse will take a stride. After all horses have taken their strides, we reach the Barrier point to 
 * check if any horse has made it past the finish line. If yes, we terminate all threads; otherwise they all start a new
 * run till the barrier point again; and this happens automatically.
 */

class Horse implements Runnable {
	private static int counter = 0;
	private int id = counter++;
	private static Random rand = new Random(47);
	private int strides = 0;
	private CyclicBarrier cb;
	
	public Horse(CyclicBarrier cb) {
		this.cb = cb;
	}
	
	//Take a stride
	public void stride() {
		strides += rand.nextInt(3); //will generate 0, 1, 2
	}
	public synchronized int getStrides() {
		return strides;
	}
	public String toString() {
		return "Horse: " + id + " ";
	}
	//Function to display the strides of each horse.
	public String tracks() {
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < getStrides(); ++i) 
			sb.append("*");
		sb.append(" " + id);
		return sb.toString();
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				synchronized(this) {
					stride();
				}
				//If all threads/parties have called await(), then we have reached the barrier point
				//else this call will block.
				cb.await();
			}
		}catch(InterruptedException e) {
			System.out.println(this + " interrupted");
		}catch(BrokenBarrierException e) {
			throw new RuntimeException(e);
		}
	}
}
public class HorseRace {
	//length of the race track
	private static final int FIELD_LENGTH = 75;
	private CyclicBarrier cb = null;
	private List<Horse> horseList = new ArrayList<Horse>();
	private ExecutorService exec = Executors.newCachedThreadPool();
	HorseRace(int nHorses, final int pause) {
		cb = new CyclicBarrier(nHorses, new Runnable() { //This is the thread which executes when all parties reach the barrier point.
			//This runnable thread is called the barrier action.
			public void run() {
				StringBuilder sb = new StringBuilder();
				for(int i = 0; i < FIELD_LENGTH; ++i)
					sb.append("=");
				System.out.println(sb.toString());
				
				//Display the strides of each horse
				for(Horse h : horseList)
					System.out.println(h.tracks());
				//Check if any horse has crossed the finish line. If yes, we will terminate all threads;
				//else the threads will automatically start blocking when they call await();
				for(Horse h : horseList) {
					if(h.getStrides() >= FIELD_LENGTH) {
						System.out.println(h + " won!!");
						exec.shutdownNow();
						return;
					}
				}
				try {
					TimeUnit.MILLISECONDS.sleep(pause);
				} catch(InterruptedException e) {
					System.out.println("barrier-action sleep interrupted");
				}
			}
		});
		for(int i = 0; i < nHorses; ++i) {
			Horse h = new Horse(cb);
			horseList.add(h);
			exec.execute(h);
		}				
	}
	public static void main(String[] args) {
		new HorseRace(7, 100);
	}
}

/*
Please read DelayQueueDemo.java next
*/