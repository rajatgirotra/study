import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.PriorityBlockingQueue;
import java.util.concurrent.TimeUnit;


/*
 * Please read DelayQueueDemo.java first
 * PriorityBlockingQueue is a BlockingQueue which takes out objects from the queue based on its priority.
 * We'll create a PriorityBlockingQueue in which each entry is a task with a given priority.
 * Then we'll create Producer and Consumer classes which will produce and consume these tasks
 */
class PrioritizedTask implements Runnable, Comparable<PrioritizedTask> {
    private static int counter = 0;
    protected static List<PrioritizedTask> taskList = new ArrayList<PrioritizedTask>();

    //using random to simulate the run operation.
    private Random rand = new Random(47);
    private int id = counter++;
    private int priority;

    public PrioritizedTask(int pri) {
        priority = pri;
        taskList.add(this);
    }

    //implement Comparable for ordering the objects inside the queue.
    public int compareTo(PrioritizedTask arg) {
        if (this.priority < arg.priority) {
            return 1;
        }

        if (this.priority > arg.priority) {
            return -1;
        }

        return 0;
    }

    public String toString() {
        return String.format("[%1$-3d]", priority) + " Task " + id;
    }

    public String summary() {
        return "(" + id + ": " + this.priority + ")";
    }

    public void run() {
        try {
            TimeUnit.MILLISECONDS.sleep(rand.nextInt(250));
        } catch (InterruptedException e) {
            System.out.println(this + " interrupted");
        }

        System.out.println(this);
    }

    //static class to signal the end of demo
    public static class EndSentinel extends PrioritizedTask {
        ExecutorService exec;

        public EndSentinel(ExecutorService e) {
            //Add with lowest priority so that this gets executed at the end.
            super(-1);
            exec = e;
        }

        //run method to terminate the demo
        public void run() {
            int count = 0;

            for (PrioritizedTask pt : taskList) {
                System.out.println(pt.summary());

                if ((++count % 5) == 0) {
                    System.out.println();
                }
            }

            //Terminate now
            System.out.println();
            System.out.println(this + " calling shutdownNow()");
            exec.shutdownNow();
        }
    }
}


class PrioritizedTaskProducer implements Runnable {
    private Queue<PrioritizedTask> q = null;
    private ExecutorService exec;
    private Random rand = new Random(47);

    public PrioritizedTaskProducer(Queue<PrioritizedTask> q, ExecutorService e) {
        this.q = q;
        exec = e;
    }

    public void run() {
        //Add tasks randomly to the queue of varying priorities.
        for (int i = 0; i < 20; ++i) {
            q.add(new PrioritizedTask(rand.nextInt(10)));
            Thread.yield();
        }

        try {
            //Now add some high priority tasks
            for (int i = 0; i < 10; ++i) {
                TimeUnit.MILLISECONDS.sleep(250);
                q.add(new PrioritizedTask(10));
            }

            //Add some more: lowest priority jobs first
            for (int i = 0; i < 10; ++i) {
                q.add(new PrioritizedTask(i));
            }

            //Add the end sentinel job to terminate the application.
            q.add(new PrioritizedTask.EndSentinel(exec));
        } catch (InterruptedException e) {
            System.out.println("PrioritizedTaskProducer interrupted");
        }
    }
}

class PrioritizedTaskConsumer implements Runnable {
	private PriorityBlockingQueue<PrioritizedTask> q = null;
	
	public PrioritizedTaskConsumer(PriorityBlockingQueue<PrioritizedTask> queue) {
		q = queue;		
	}
	
	public void run() {
		try {
			while(!Thread.interrupted()) {
				q.take().run();
			}
		}catch(InterruptedException e) {
			System.out.println("PrioritizedTaskConsumer interrupted");
		}
		System.out.println("Finished PrioritizedTaskConsumer");
	}
}

public class PriorityBlockingQueueDemo {
	public static void main(String[] args) throws InterruptedException {
		ExecutorService exec = Executors.newCachedThreadPool();
		PriorityBlockingQueue<PrioritizedTask> priorityQueue = new PriorityBlockingQueue<PrioritizedTask>();
		exec.execute(new PrioritizedTaskProducer(priorityQueue, exec));
		//TimeUnit.SECONDS.sleep(5);
		exec.execute(new PrioritizedTaskConsumer(priorityQueue));
	}
}

/*
 * Please read Pool.java next
 */
