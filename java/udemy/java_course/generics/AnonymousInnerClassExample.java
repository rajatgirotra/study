/*
 * An anonymous inner class is a class which is created inside a function and you
 * 1) will only ever create one object of; not more than one
 * 2) the class is defined together with the object creation in the same java statement
 * 3) the anonymous inner class can extend some class or implement some interface.
 * 4) You create the anonymous inner class simple by creating an object of a normal class, followed by the class body inside {}. See below.
 */

package generics;

class Animal {
    public void makeNoise() {
        System.out.println("Generic animal cannot make a noise");
    }
}



public class AnonymousInnerClassExample {
    public static void main(String[] args) {
        Animal generic = new Animal(); // regular Animal object
        generic.makeNoise();

        // anonymous inner class extending Animal
        Animal dog = new Animal() {
            @Override
            public void makeNoise() {
                System.out.println("Woof Woof!!");
            }
        };
        System.out.println("dog variable class type is: " + dog.getClass().getName());


        // anonymous inner class implementing Runnable
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                System.out.println("I am an anonymous runnable");
            }
        };
        System.out.println("runnable variable class type is: " + runnable.getClass().getName());

        dog.makeNoise();
        runnable.run();
    }    
}

/* Please read OptionalExample.java next */