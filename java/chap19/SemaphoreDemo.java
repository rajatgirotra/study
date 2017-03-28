import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;


/*
 * Please read Fat.java first
 */
class CheckoutTask<T> implements Runnable {
    private static int counter = 0;
    private final int id = counter++;
    private Pool<T> pool = null;

    //C'tor
    public CheckoutTask(Pool<T> objectPool) {
        pool = objectPool;
    }

    public void run() {
        //Check out an item first;
        try {
            T item;
            item = pool.checkOut();
            System.out.println(this + " checkedout " + item);
            //Wait for some time 
            TimeUnit.SECONDS.sleep(1);
            //Check back in
            System.out.println(this + " checking in " + item);
            pool.checkIn(item);
        } catch (InterruptedException e) {
        }
    }

    public String toString() {
        return "CheckoutTask: " + id + "  ";
    }
}


public class SemaphoreDemo {
    final static int SIZE = 25;

    public static void main(String[] args) throws Exception {
        ExecutorService exec = Executors.newCachedThreadPool();

        //Create a pool of objects.
        final Pool<Fat> objectPool = new Pool<Fat>(Fat.class, SIZE);

        //these tasks will repeatedly checkOut and checkIn from the pool.
        for (int i = 0; i < SIZE; i++)
            exec.execute(new CheckoutTask<Fat>(objectPool));

        System.out.println("All CheckoutTasks created");

        List<Fat> list = new ArrayList<Fat>();

        for (int i = 0; i < SIZE; i++) {
            Fat f = objectPool.checkOut();
            System.out.print(i + ": main() thread checked out ");
            f.operation();
            list.add(f);
        }
        
        //Pool is completely checkedOut now, so checking out further will block.
        Future<?> blocked = exec.submit(new Runnable() {
        	public void run() {
        		try {        			
        			// Semaphore prevents additional checkout,
        			// so call is blocked:
        			objectPool.checkOut();
        		} catch(InterruptedException e) {
        			System.out.println("checkOut() Interrupted");
        		}
        	}
        });
        TimeUnit.SECONDS.sleep(2);
        blocked.cancel(true); // Break out of blocked call

        //now check back in
        System.out.println("Checking in objects in " + list);
        for(Fat f : list)
        	objectPool.checkIn(f);
        for(Fat f : list)
        	objectPool.checkIn(f); // Second checkIn ignored
        exec.shutdown();
    }
}

/*
Please read ExchangerDemo.java next
*/