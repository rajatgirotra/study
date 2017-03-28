import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.Exchanger;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import net.mindview.util.*;

/*
 * Please read SemaphoreDemo.java first
 * Another threading aid is the Exchanger class. This class has a barrier point just like the
 * CyclicBarrier at which the two tasks exchange their references.
 * For example, consider a Producer and consumer scenario in which the producer takes long to
 * produce. In such a case both the Producer and Consumer classes contain a reference to the 
 * Exchanger class. Then when both the exchanger references call the exchange() method, the 
 * barrier point is reached and the two references are exchanges as shown below:
 * 
 */

class ExchangerProducer<T> implements Runnable {
	private Generator<T> gen;

	//The exchanger object
	Exchanger<List<T>> exchanger;

	//the list holder
	List<T> holder;

	public ExchangerProducer(Exchanger<List<T>> exch, Generator<T> gen, List<T> holder) {
		this.gen       = gen;
		this.exchanger = exch;
		this.holder    = holder;		
	}

	public void run() {
		try {
			while(!Thread.interrupted()) {
				for(int i = 0; i < ExchangerDemo.size; ++i)
					holder.add(gen.next());

				//Now that the producer container is full, we exchange it for 
				//the empty container.
				//Note, that this call will block till the Consumer class calls its
				//exchanger.exchange() method.
				holder = exchanger.exchange(holder);
			}
		} catch(InterruptedException e) {

		}
	}	
}

class ExchangerConsumer<T> implements Runnable {
	private List<T> holder;
	private Exchanger<List<T>> exchanger;
	private volatile T value;
	public ExchangerConsumer(Exchanger<List<T>> exchanger, List<T> holder) {
		this.holder = holder;
		this.exchanger = exchanger;
	}

	public void run() {
		//Simply exchange the List<T> from consumer
		try {
			while(!Thread.interrupted()) {
				holder = exchanger.exchange(holder);
				//Now the holder is full, so we can manipulate it.
				for(T x : holder) {
					value = x;
					holder.remove(x);
				}
			}
		} catch (InterruptedException e) {			
		}
		System.out.println("Final Value: " + value);
	}
}
public class ExchangerDemo {
	static int size = 10;
	static int delay = 5; // Seconds
	public static void main(String[] args) throws Exception {
		if(args.length > 0)
			size = new Integer(args[0]);
		if(args.length > 1)
			delay = new Integer(args[1]);
		ExecutorService exec = Executors.newCachedThreadPool();
		Exchanger<List<Fat>> xc = new Exchanger<List<Fat>>();
		List<Fat>
		producerList = new CopyOnWriteArrayList<Fat>(),
		consumerList = new CopyOnWriteArrayList<Fat>();
		exec.execute(new ExchangerProducer<Fat>(xc,
				BasicGenerator.create(Fat.class), producerList));
		exec.execute(new ExchangerConsumer<Fat>(xc,consumerList));
		TimeUnit.SECONDS.sleep(delay);
		exec.shutdownNow();
	} 
}
