/*
 * Please read Pool.java first
 */
public class Fat {
    private static int counter = 0;
    private volatile double d; // volatile means no optimization
    private final int id = counter++;

    public Fat() {
        // Expensive, interruptible operation:
        for (int i = 1; i < 10000; i++) {
            d += ((Math.PI + Math.E) / (double) i);
        }
    }

    public String toString() {
        return "Fat: " + id;
    }

    public void operation() {
        System.out.println(this);
    }
}

/*
We’ll pool these objects to limit the impact of this constructor. We can test the Pool class by creating a task 
that will check out Fat objects, hold them for a while, and then check them back in:

Please read SemaphoreDemo.java next
*/