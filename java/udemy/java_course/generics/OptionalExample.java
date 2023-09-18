package generics;

import java.util.NoSuchElementException;
import java.util.Optional;

/* Optional is just like c++ optional. */

class Cat {
    private String name;
    private Integer age;

    public Cat(String name, Integer age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return this.name;
    }

    public Integer getAge() {
        return this.age;
    }

    @Override
    public String toString() {
        return String.format("Cat: %s, Age: %d", this.name, this.age);
    }
}


public class OptionalExample {

    public static Cat findCatByName(String name) {
        Cat cat = new Cat("Fred", 3); // simulate finding a Cat in some DB maybe.
        // return cat;
        return null;
    }

    public static Optional<Cat> findOptionalCatByName(String name) {
        Cat cat = new Cat("Fred", 3); // simulate finding a Cat in some DB maybe.
        // return an optional
        return Optional.ofNullable(cat);
        // return Optional.ofNullable(null);
        // return Optional.of(cat); //use Optional.of() when yuo are sure that the cat variable will 100% be valid and not null. otherwise use ofNullable()
    }

    public static void main(String[] args) {        
        Cat myCat = findCatByName("Fred");

        if(myCat != null) {
            System.out.println("Age is: " + myCat.getAge());
        } else {
            System.out.println("Default Age is: 0");
        }
        

        // what if findCatByName returns a null as not Cat object is found in DB. You will get NullPointerException.
        // that's why java 8 introduced optional
        Optional<Cat> optCat = findOptionalCatByName("Fred");

        // how to retrieve optional?
        if(optCat.isPresent()) {
            System.out.println(optCat.get().getAge());
        } else {
            System.out.println("Default Age is: 0");
        }

        // but this is same as not using Optional. instead of explicitly checking for null, we are using isPresent(). Yes that's right. But now we are
        // explicitly telling the user of the API that null may be returned, so the user must take caution.

        // Also Optional provides other API's.
        myCat = optCat.orElse(new Cat("UNKNOWN", 0));
        System.out.println(myCat);

        try {
            // var age = optCat.get().getAge(); // Optional.get() will throw "NoSuchElementException" if the optional is empty
            var age = optCat.orElseThrow().getAge(); // Optional.orElseThrow() is same get()
            System.out.println("Optional.get(), age is: " + age);
        } catch(NoSuchElementException e) {
            e.printStackTrace();
        }

        // map returns special value Optional.empty if optional is empty,
        // otherwise it will fetch the age and return an Optional<Integer>
        var age2 = optCat.map(Cat::getAge);
        System.out.println("Age using Optional.map: " + age2); 
        System.out.println("Type of age2: " + age2.getClass().getName()); // returns an 

        var age3 = optCat.map(Cat::getAge).orElse(0);
        System.out.println("Age using Optional.map: " + age3); 
        System.out.println("Type of age3: " + age3.getClass().getName()); // returns an 

    }
}