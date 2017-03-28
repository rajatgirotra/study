/*
 * Please read CaptureUncaughtException.java first
 * What we'll do here is that we'll create a producer-consumer scenario where producer will produce even numbers
 * and the consumer will only check if the numbers produced are even. If not it will fail.
 * Here we create an abstract class from which we can create a producer.
 */
public abstract class IntGenerator {
	private volatile boolean bCanceled = false;
	public abstract int next();
	public void cancel() {
		bCanceled = true;
	}
	public boolean isCanceled() {
		return bCanceled;
	}
}

/*
Next we'll create an EvenChecker class which will be the consumer. It will implement the Runnable interface
Please read EvenChecker.java next
*/