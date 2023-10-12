/*
 * So you already read that you need a FunctionalInterface for lambda expression.
 * Lets talk about some of the important Functional interfaces in java which truly enable functional programming.
 * 
 * These are Function, Supplier, Consumer, Predicate.
 * 
 * These are defined like these
 * 
 * @FunctionalInterface
 * interface Function<T, R>
 * {
 *     R apply(T t); // maps a value of type T to type R.
 * }
 * 
 * @FunctionalInterface
 * interface Supplier<T>
 * {
 *     T get(); // is a producer of a value of type T
 * }
 * 
 * @FunctionalInterface
 * interface Consumer<T>
 * {
 *     void accept(T t); // is a consumer of a value of type T
 * }
 * 
 * @FunctionalInterface
 * interface Predicate<T>
 * {
 *     boolean test(T t); // accepts a value of type T and returns a boolean. (Its a boolean predicate)
 * }
 * Lets see how these are used.
 */
package org.generics;

import java.security.SecureRandom;
import java.sql.SQLOutput;
import java.util.Random;
import java.util.function.BiConsumer;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.random.RandomGenerator;

class Person2 {
    private String name;
    private String email;
    private int age;
    private int exp_in_yrs;

    public Person2(String name, String email, int age, int exp_in_yrs) {
        this.name = name;
        this.email = email;
        this.age = age;
        this.exp_in_yrs = exp_in_yrs;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public int getAge() {
        return age;
    }

    public int getExp_in_yrs() {
        return exp_in_yrs;
    }

    @java.lang.Override
    public java.lang.String toString() {
        return "Person2{" +
                "name='" + name + '\'' +
                ", email='" + email + '\'' +
                ", age=" + age +
                ", exp_in_yrs=" + exp_in_yrs +
                '}';
    }
}

class Employee {
    String name;
    String email;
    String id;

    public Employee(String name, String email, String id) {
        this.name = name;
        this.email = email;
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public String getId() {
        return id;
    }

    @Override
    public String toString() {
        return "Employee{" +
                "name='" + name + '\'' +
                ", email='" + email + '\'' +
                ", id='" + id + '\'' +
                '}';
    }
}

public class FunctionalProgramming {

    private static int empCount = 0;
    public static String Person2ToEmployeeId_one(Person2 Person2) {
        return Person2.getEmail().toLowerCase();
    }

    public static String Person2ToEmployeeId_two(Person2 Person2) {
        ++empCount;
        return Person2.getName().replaceAll(" ", "") + empCount;
    }

    public static String generateEmployeeId(Person2 p, Function<Person2, String> mapToId) {
        return mapToId.apply(p);
    }

    public static Employee generateEmployee(Person2 p) {
//        return new Employee(p.getName(), p.getEmail(),
//                generateEmployeeId(p, FunctionalProgramming::Person2ToEmployeeId_one));

        return new Employee(p.getName(), p.getEmail(),
                generateEmployeeId(p, FunctionalProgramming::Person2ToEmployeeId_two));

    }

    public static void main(String[] args) {
        // Function is used to transform one type to another
        Person2 p = new Person2("Rajat Girotra", "RAJATGIROTA@yahoo.com", 40, 20);
        Employee e = generateEmployee(p);
        System.out.println(e);


        // Simple Supplier to generate an Integer value.
        Supplier<Integer> randomNumber = () -> {
            return new SecureRandom().nextInt(100);
        };

        // Simple consumer to consume the integer values.
        Consumer<Integer> consumer = value -> System.out.println(value);

        consumer.accept(randomNumber.get());

        // BiConsumer which takes two values. Adds 1 to first value and multiplies the result by the second value
        BiConsumer<Integer, Integer> add1AndMultiply = (first, second) -> {
            System.out.println("BiConsumer: " + (first+1) * second);
        };

        add1AndMultiply.accept(3, 4);

    }

    // Similarly Supplier, Consumer and Predicate are trivial.
    // Supplier can be used to supply a value only when needed (if the supplied value is costly to construct,
    // and may not even be used. consider using the Supplier interface)

    // We even have BiFunction<T, U, R> which takes two parameters T and U and returns R.
    // Similarly BiConsumer<T, U> consumes two values and returns void.

    // Let's move on to Streams API in Java 8 now.
    // Read StreamsPlay.java next

}
