import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;


/*
 * Please read PriorityBlockingQueue.java first.
 * We'll look into JAVA semaphores now.
 * Conceptually, a semaphore maintains a set of permits. Each acquire() blocks if necessary until a permit
 * is available, and then takes it. Each release() adds a permit, potentially releasing a blocking acquirer.
 * However, no actual permit objects are used; the Semaphore just keeps a count of the number available and
 * acts accordingly.
 * Semaphores are often used to restrict the number of threads than can access some (physical or logical)
 * resource.
 *
 * Note that no synchronization lock is held when acquire() is called as that would prevent an item from being
 * returned to the pool. The semaphore encapsulates the synchronization needed to restrict access to the pool,
 * separately from any synchronization needed to maintain the consistency of the pool itself.
 *
 * The constructor for this class optionally accepts a fairness parameter. When set false, this class makes
 * no guarantees about the order in which threads acquire permits. In particular, barging is permitted, that is,
 * a thread invoking acquire() can be allocated a permit ahead of a thread that has been waiting - logically
 * the new thread places itself at the head of the queue of waiting threads. When fairness is set true, the semaphore
 * guarantees that threads invoking any of the acquire methods are selected to obtain permits in the order in
 * which their invocation of those methods was processed (first-in-first-out; FIFO). Note that FIFO ordering
 * necessarily applies to specific internal points of execution within these methods. So, it is possible for
 * one thread to invoke acquire before another, but reach the ordering point after the other, and similarly
 * upon return from the method.
 *
 * Also note that the untimed tryAcquire methods do not honor the fairness setting, but will take any permits
 * that are available.
 *
 * Here we'll first create a Pool of objects and then use semaphore on that
 */
public class Pool<T> {
    private volatile boolean[] checkedOut;
    private Semaphore sema = null;
    private List<T> poolList = new ArrayList<T>();
    private int size;

    public Pool(Class<T> type, int size) {
        this.size = size;
        checkedOut = new boolean[size];
        sema = new Semaphore(size, true);

        for (int i = 0; i < size; ++i) {
            try {
                poolList.add(type.newInstance());
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
    }

    public T checkOut() throws InterruptedException {
        //acquire a semaphore first; then call getItem() to get the item from the pool.
        sema.acquire();

        return getItem();
    }

    public synchronized T getItem() {
        for (int i = 0; i < size; ++i) {
            if (!checkedOut[i]) {
                checkedOut[i] = true;

                return poolList.get(i);
            }
        }

        return null; //The semaphore prevents us from reaching here.
    }

    public void checkIn(T item) {
        if (releaseItem(item)) {
            sema.release();
        }
    }

    public synchronized boolean releaseItem(T item) {
        int index = poolList.indexOf(item);
        if (index == -1) {
            return false;
        }
        if (checkedOut[index]) {
            checkedOut[index] = false;
            return true;
        }
        return false;
    }
}

/* 
 * Next we create a class whose c'tor takes time to run, so we allocate all objects initially at start-up.
 * Please read Fat.java next
 */
