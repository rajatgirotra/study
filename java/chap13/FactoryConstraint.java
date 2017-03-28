/*
 * Please read InstantiateGenericType.java first.
 */

interface FactoryI<T> {
	public T create();
}

class IntegerFactory implements FactoryI<Integer> {
	public Integer create() {
		return new Integer(8);
	}
}

class Widget {
	public static class Factory implements FactoryI<String> {
		public String create() {
			return new String("Hello World");
		}
	}
}

class Foo2<T> {
	private T element;
	public <F extends FactoryI<T>> Foo2(F ref) {
		element = ref.create();
	}
	public String toString() {
		return element.toString();
	}
}
public class FactoryConstraint {
	public static void main(String[] args) {
		System.out.println(new Foo2<Integer>(new IntegerFactory()));
		System.out.println(new Foo2<String>(new Widget.Factory()));
	}
}

/*
please read ListOfGenerics.java next
*/