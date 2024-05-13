Very trivial.

public class Printer <T> {

};

public class Map <Key, Value> {

};

public class Map <T extends Animal> {
    // T extends Animal is a bounded generic. and Animal can be any class or interface.
    // We call this an upper bound; as T cannot be anything other than Animal or its derived classes
};

// let say a class T extends Animal and implements Serializable. and you want your generic parameter to be any such class. Then you do
public class GenericClass <T extends Animal & Serializable>
// just remember that class should be first followed by interfaces.


// template functions are also very trivial.

public static <Key, Value> Value doSomething(Key key, Value value) {
    // do something..
    return value;
}


// generic wildcards.
Let say you have List<Cats> cats. and a function expects List<Object>
void do(List<Object> lst) {
}
calling do(cats); will result in compile time error. Although Cat is derived from Object, but List<Cat> doesn't derive from List<Object>,
 so it's not possible. The workaround is to use a generic wildcard.

void do(List<?> lst) {
    // ? just means I am not sure the generic type of List, so basically allow everything.
}
or can also specify a bounded generic with wildcard
void do(List<? extends Animal> lst) {
    for(var item : lst) {
        item.makeNoise(); // this should work
    }
}

Another bounded generic is <T super Animal>
Lets assume we have the following hierarchy of classes.

Object -> Animal 
Animal -> Cat
Animal -> Dog
Cat -> Manx
Dog -> Terrier

public class MyClass<T super Cat> { // this isn't allowed
// why? because of type erasure.
}

----------------------------------------------------------
Type erasure in java.
In Java, the generic type information is only available at compile time. These types are discarded after compilation, so the JVM has no clue about the run-time type information
 of the generic types. This is called type erasure.

 What does it mean?
 1. It means that you cannot access anything inside the generic type at runtime. Example:
 public class MyClass<T> {
          T obj;
          public void doSomething() {
                if(obj instanceof T) { // this is ALLOWED. Because the compiler can check the type of obj at compile time.
                }

                obj = new T(); // this is not allowed. See GenericConstraints.java for more.

                System.out.println(obj.getClass().getName()); // this is allowed as you are accessing the class of obj at runtime.
                System.out.println(T.class.getName()); // this is not allowed, because T is not available at runtime.
          }
     }

2. Because of type erasure
public class Node<T super Animal> { // T can be Animal or any of its super classes, all the way to Object.
    private T obj;
    private Node<T> next;
}

should reduce to
public class Node {
    private Object obj;
    private Node next;
}

So basically the type T is always erased to Object. this means Node class could be instantiated with Animal or any of its super class, but it will always be treated as Object.
So affecting there is no bound. At run-time, you can put anything in "obj", like a totally unrelated class.

See GenericsPlayground.java for more


