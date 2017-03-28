/*
 * Simple program to implement Callable<V> interface.
 * This is a very important program. You must understand what is mentioned in the comments below.
 */

import java.util.concurrent.*;
import java.util.List;
import java.util.ArrayList;

public class CallableDemo implements Callable<String> {
	int id;
	public CallableDemo(int i) {
		this.id = i;
	}
	
	/*
	 * For Runnable, you implement public void run() &
	 * for Callable<V>, you implement public V call() function.
	 */
	public String call() {		
		try {
			TimeUnit.SECONDS.sleep(5);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(id);
		return "Callable Demo object: " + id; 
	}
	
	public static void main(String[] args) throws Exception {
		List<Future<String>> results = new ArrayList<Future<String>>();
		ExecutorService exec = Executors.newCachedThreadPool(); 
		
		for(int i = 0; i < 10; ++i) {
			//For Runnable, you call ExecutorService.execute() method.
			//For Callable<V>, you call ExecutorService.submit() method.
			//Now, the moment submit gets called, the JVM creates a dummy return object
			//of type Future<V>, and places it in the list. So the for loop completes immediately
			//and it does not have to wait for each of the threads created here, and each thread may finish at 
			//its own pace.
			//So the Sysout("A"); is output immediately.
			results.add(exec.submit(new CallableDemo(i)));
			
			//if instead of putting the dummy object in the list, we call the get() function.
			//the get function() first checks if the thread has finished. If no, this call will block.
			//until the thread finishes. If yes, this will return the actual return type V.
			//You can also check if a thread has finished or not by using
			//the Future<V>.isDone() method which returns either true or false.
			//System.out.println(exec.submit(new CallableDemo(i)).get()); //--> This call makes the threads synchronous.
		}
		
		System.out.println("A");
		for(Future<String> fs : results) {			
			System.out.println(fs.isDone());
			System.out.println(fs.get());
		}
		exec.shutdown(); //You should never forget to call this.
	}
}

/*
Please read Sleeping.java next
*/