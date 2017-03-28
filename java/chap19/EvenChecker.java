import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/*
 * Please read IntGenerator.java first
 */
public class EvenChecker implements Runnable {
	private IntGenerator ig;
	private int id; //Each EvenChecker consumer will have an id and an IntGenerator producer.

	public EvenChecker(IntGenerator ig, int id) {
		this.ig = ig;
		this.id = id;
	}

	public void run() {
		while(!ig.isCanceled()) {
			int val = ig.next();
			if(val % 2 != 0) {
				System.out.println("EvenChecker consumer no: " + id + "     " + val + " is not even");
				ig.cancel();			
			}
			else {
				System.out.println("EvenChecker consumer no: " + id + "     " + val + " is even");
			}
		}
	}
	
	public static void test(IntGenerator ig, int count) {
		ExecutorService exec = Executors.newCachedThreadPool();
		for(int i = 0; i < count; ++i) {
			exec.execute(new EvenChecker(ig, i));
		}
		exec.shutdown();
	}
	
	public static void test(IntGenerator ig) {
		test(ig, 10);
	}
}

/*
Next we'll create the producer which extends from IntGenerator
Please read EvenGenerator.java next
*/