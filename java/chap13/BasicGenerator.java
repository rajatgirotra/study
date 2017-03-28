/*
 * Please read Generators.java first
 * Lets try to create a BasicGenerator class that will be used to create objects of any class.
 * This class will implement the Generator interface and override the next() method.
 */
import generics.coffee.*;

public class BasicGenerator<T> implements Generator<T> {
	private Class<T> type;
	public BasicGenerator(Class<T> type) {
		this.type = type;
	}
	
	public T next() {
		try {
			return type.newInstance();			
		}catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
	
	public static <T> Generator<T> create(Class<T> type) {
		return new BasicGenerator<T>(type);
	}
}

/*
Please read CountedObject.java next
*/