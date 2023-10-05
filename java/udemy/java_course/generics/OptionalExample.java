package org.example;

import java.util.NoSuchElementException;
import java.util.Optional;

/* Optional is just like c++ optional. */

class Cat2 {
    private String name;
    private Integer age;

    public Cat2(String name, Integer age) {
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
        return String.format("Cat2: %s, Age: %d", this.name, this.age);
    }
}


public class OptionalExample {

    public static Cat2 findCat2ByName(String name) {
        Cat2 Cat2 = new Cat2("Fred", 3); // simulate finding a Cat2 in some DB maybe.
        // return Cat2;
        return null;
    }

    public static Optional<Cat2> findOptionalCat2ByName(String name) {
        Cat2 Cat2 = new Cat2("Fred", 3); // simulate finding a Cat2 in some DB maybe.
        // return an optional
//        return Optional.ofNullable(Cat2);
         return Optional.ofNullable(null);
        // return Optional.of(Cat2); //use Optional.of() when yuo are sure that the Cat2 variable will 100% be valid and not null. otherwise use ofNullable()
    }

    public static void main(String[] args) {        
        Cat2 myCat2 = findCat2ByName("Fred");

        if(myCat2 != null) {
            System.out.println("Age is: " + myCat2.getAge());
        } else {
            System.out.println("Default Age is: 0");
        }
        

        // what if findCat2ByName returns a null as no Cat2 object is found in DB. You will get NullPointerException.
        // that's why java 8 introduced optional
        Optional<Cat2> optCat2 = findOptionalCat2ByName("Fred");

        // how to retrieve optional?
        if(optCat2.isPresent()) {
            System.out.println(optCat2.get().getAge());
        } else {
            System.out.println("Default Age is: 0");
        }

        // but this is same as not using Optional. instead of explicitly checking for null, we are using isPresent(). Yes that's right. But now we are
        // explicitly telling the user of the API that null may be returned, so the user must take caution.

        // Also Optional provides other API's.
        myCat2 = optCat2.orElse(new Cat2("UNKNOWN", 0));
        System.out.println(myCat2);

        try {
            // var age = optCat2.get().getAge(); // Optional.get() will throw "NoSuchElementException" if the optional is empty
            var age = optCat2.orElseThrow().getAge(); // Optional.orElseThrow() is same get()
            System.out.println("Optional.get(), age is: " + age);
        } catch(NoSuchElementException e) {
            e.printStackTrace();
        }

        // map returns special value Optional.empty if optional is empty,
        // otherwise it will fetch the age and return an Optional<Integer>
        var age2 = optCat2.map(Cat2::getAge);
        System.out.println("Age using Optional.map: " + age2); 
        System.out.println("Type of age2: " + age2.getClass().getName()); // returns an 

        var age3 = optCat2.map(Cat2::getAge).orElse(0);
        System.out.println("Age using Optional.map: " + age3); 
        System.out.println("Type of age3: " + age3.getClass().getName()); // returns an 

    }
}

/*
 * Please read LambdaExpression.java next
 */